#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<fcntl.h>
#include<unistd.h>
#include<signal.h>
#include<sys/time.h>
#include<signal.h>
#include<unistd.h>
#include<fcntl.h>
#include<pthread.h>
#include"tl_controlling.h"
#include "include/libconfig.h"
#include"tl_message.pb-c.h"
#include "zmq.h"

#define ON	1
#define OFF	0

static int hc595_fd;
static unsigned char light_status[6];		//灯亮灭状态
static unsigned int timer_count = 0;
static TrafficLight trafficlight[16];		//16个交通灯
static TrafficLight_Phase light_phase[8];	//8个相位
static int g_light_num = 0;		//交通灯数量
static int regular_light_num = 0;	//常规交通灯数量
static int g_phase_num = 0;		//相位数
static int g_phase_no = 0;		//当前运行相位
static char *g_ip_url;
static int g_run_time = 0;
static short g_restore_phase = 0;	//恢复相位
static short g_restore_time = -1;	//恢复相位时间
static short g_insert_phase = -1;	//插入相位
static char g_yellow_light = 0;
static char g_delay_flag = 0;
//zmq发送红绿灯信息
TflightPackage__TFLightCtrlInfo tflight_ctrl_info = TFLIGHT_PACKAGE__TFLIGHT_CTRL_INFO__INIT;
static char g_insert_phase_flag = 0;;
pthread_mutex_t tl_mutex_lock;

static void trafficlight_write(Direction dir, Toward to, LightType light, char value);

static void print_trafficlight()
{
	int i;
	printf("---------trafficlight work---------\n");
	printf("phase: %d  last_time: %d run_time: %d count %d\n", g_phase_no, light_phase[g_phase_no].time_count, g_run_time, timer_count);
	for(i = 0; i < g_light_num; i++)
	{
		printf("No %d: ", i+1);
		switch(trafficlight[i].dir[0])
		{
			case east:
				printf("east  ");
				break;
			case west:
				printf("west  ");
				break;
			case south:
				printf("south ");
				break;
			case north:
				printf("north ");
				break;
		}
		
		switch(trafficlight[i].to[0])
		{
			case left:
				printf("left   ");
				break;
			case front:
				printf("front  ");
				break;
			case right:
				printf("right  ");
				break;
			case pedestrian:
				printf("people ");
				break;
		}
		
		switch(trafficlight[i].cur_status)
		{
			case red:
				printf("red    ");
				break;
			case green:
				printf("green  ");
				break;
			case yellow:
				printf("yellow ");
				break;
		}
		printf("time %02d\n", trafficlight[i].last_time);
	}
	
}

//func:change trafficlight status
//no:trafficlight number
//light:trafficlight status
//value:ON OFF
//return:void
void trafficlight_controlling(int no, LightType light, char value)
{
	int i;
	for(i = 0; i < trafficlight[no].num; i++)
	{		
		if(trafficlight[no].to[i] != pedestrian || light != yellow)
				trafficlight_write(trafficlight[no].dir[i], trafficlight[no].to[i], light, value);
	}
}

static void set_timer(char on, int value)
{
	struct itimerval val, val_interval;
	
	timer_count = 0;
	if(on == 1)
	{
		val.it_value.tv_sec = 0;
		val.it_value.tv_usec = 1;
	}
	else
	{
		val.it_value.tv_sec = 0;
		val.it_value.tv_usec = 0;
	}
	
	val_interval.it_value.tv_sec = 0;
	val_interval.it_value.tv_usec = value * 1000;
	
	val.it_interval = val_interval.it_value;
	
	setitimer(ITIMER_REAL, &val, NULL);
	
}

//func:change the phase,then calculate every phase time.
//mode:1-first insert, yellow.
//		 2-second insert,green.
//		 3-first restore,yellow.
//		 4-second restore,green. 
//return:void
void calc_last_time(char mode, char cur_phase, char last_phase, char insert_phase)
{
	int i;
	int time;
	
	if(g_insert_phase % 2 == 0)
		time = light_phase[cur_phase].last_time;
	else
		time = light_phase[cur_phase].time_count;
	
	switch(mode)
	{
		//第一次插入，先闪黄灯
		case 1:
			for(i = 0; i < regular_light_num; i++)
			{
				//first insert,current phase time = yellow time.
				if(trafficlight[i].dir[0] == light_phase[cur_phase].dir && (trafficlight[i].to[0] == light_phase[cur_phase].to))
				{
					trafficlight[i].last_time = time;
					continue;
				}
				//insert phase time = yellow time.
				if((trafficlight[i].dir[0] == light_phase[insert_phase].dir) && (trafficlight[i].to[0] == light_phase[insert_phase].to))
				{
					trafficlight[i].last_time = time;
					continue;
				}
				//the rest phase time += yellow time + insert_phase time + insert_phase_yellow time
				if(g_restore_time > TSP_RESTORE_TIME) {
					trafficlight[i].last_time += time + light_phase[insert_phase].last_time + light_phase[(insert_phase+1)%g_phase_num].last_time;
				}
				else {
					if(g_restore_phase % 2)
						trafficlight[i].last_time = trafficlight[i].last_time_phase[(g_restore_phase+1)%g_phase_num] + time + light_phase[insert_phase].last_time + light_phase[insert_phase+1].last_time;
					else
						trafficlight[i].last_time = trafficlight[i].last_time_phase[(g_restore_phase+2)%g_phase_num] + time + light_phase[insert_phase].last_time + light_phase[insert_phase+1].last_time;
				}
					
			}
			break;
			
		//第二次插入，插入要插入的相位
		case 2:
			printf("cur_phase %d, last_phase %d\n", cur_phase, last_phase);
			for(i = 0; i < regular_light_num; i++)
			{
				//second insert,current phase time = insert phase time.
				if((trafficlight[i].dir[0] == light_phase[cur_phase].dir) && (trafficlight[i].to[0] == light_phase[cur_phase].to))
				{
					trafficlight[i].last_time = light_phase[cur_phase].last_time;
					continue;
				}
				//last phase time = insert_phase time + yellow time.
				if((trafficlight[i].dir[0] == light_phase[last_phase].dir) && (trafficlight[i].to[0] == light_phase[last_phase].to))
				{
					trafficlight[i].last_time = light_phase[(cur_phase+1)%g_phase_num].last_time + light_phase[cur_phase].last_time;
					continue;
				}
				
			}
			break;
			
		case 3:
			for(i = 0; i < regular_light_num; i++)
			{
				//first restore, current_phase time = yellow time.
				if((trafficlight[i].dir[0] == light_phase[cur_phase].dir) && (trafficlight[i].to[0] == light_phase[cur_phase].to))
				{
					trafficlight[i].last_time = light_phase[cur_phase].last_time;
					continue;
				}
				//insert_phase time = yellow time.
				if((trafficlight[i].dir[0] == light_phase[insert_phase].dir) && (trafficlight[i].to[0] == light_phase[insert_phase].to))
				{
					trafficlight[i].last_time = light_phase[cur_phase].last_time;
					continue;
				}
				if(g_restore_time > TSP_RESTORE_TIME) {
					trafficlight[i].last_time = trafficlight[i].last_time_phase[insert_phase] - (light_phase[insert_phase].last_time - g_restore_time) \
																		+ light_phase[cur_phase].last_time;
				}else {
					if(g_restore_phase % 2) 
						trafficlight[i].last_time = trafficlight[i].last_time_phase[(g_restore_phase+1)%g_phase_num] + light_phase[cur_phase].last_time;
					else
						trafficlight[i].last_time = trafficlight[i].last_time_phase[(g_restore_phase+2)%g_phase_num] + light_phase[cur_phase].last_time;
				}
			}
			break;
			
		case 4:
			//second restore,restore time.
			if(g_restore_time > TSP_RESTORE_TIME) {
				for(i = 0; i < regular_light_num; i++)
				{
					trafficlight[i].last_time = trafficlight[i].last_time_phase[cur_phase] - (light_phase[cur_phase].last_time - g_restore_time);	
				}
				
				light_phase[cur_phase].time_count = g_restore_time;
			}

			break;
			
		default:
			break;
			
	}
}

//func:change phase and calc time.
//mode:calc time mode.
//return:void
void change_phase(char mode, char cur_phase, char last_phase, char insert_phase)
{
	int i;
	
	if(mode == 0 && cur_phase == 0)
		last_phase = g_phase_num - 1;
	
	set_timer(OFF, 500);
	for(i = 0; i < regular_light_num; i++)
	{
		if(trafficlight[i].workmode != NORMAL)
			continue;

		//close last phase trafficlight
		if((trafficlight[i].dir[0] == light_phase[last_phase].dir) && (trafficlight[i].to[0] == light_phase[last_phase].to))
		{
			trafficlight_controlling(i, trafficlight[i].cur_status, OFF);
		}
		
		//close current phase trafficlight
		if((trafficlight[i].dir[0] == light_phase[cur_phase].dir) && (trafficlight[i].to[0] == light_phase[cur_phase].to))
			trafficlight_controlling(i, trafficlight[i].cur_status, OFF);
		
		if((trafficlight[i].dir[0] == light_phase[cur_phase].dir) && (trafficlight[i].to[0] == light_phase[cur_phase].to))
		{
			trafficlight[i].cur_status = light_phase[cur_phase].cur_status;
			trafficlight[i].next_status = trafficlight[i].cur_status ? trafficlight[i].cur_status -1 : red;
			if(mode == 0)
				trafficlight[i].last_time = light_phase[cur_phase].last_time;
			trafficlight_controlling(i, trafficlight[i].cur_status, ON);
		}
		else
		{
			trafficlight[i].cur_status = red;
			trafficlight[i].next_status = trafficlight[i].cur_status ? trafficlight[i].cur_status -1 : red;
			if(mode == 0)
				trafficlight[i].last_time = trafficlight[i].last_time_phase[cur_phase];
			trafficlight_controlling(i, red, ON);
		}
	}
	write(hc595_fd, light_status, 6);
	light_phase[cur_phase].time_count = light_phase[cur_phase].last_time;
	g_phase_no = cur_phase;
	g_run_time = 0;
	timer_count = 0;

	if(mode != 0)
		calc_last_time(mode, cur_phase, last_phase, insert_phase);
	
	set_timer(ON, 500);
	print_trafficlight();
	pthread_mutex_unlock(&tl_mutex_lock);
}

//func:TSP strategy
//mode:1-stay phase
//		 2-delay phase
//		 3-cut phase
//		 4-insert phase
//		 5-restore phase
//phase:insert phase
//return:void
void TSP_controlling(char mode, short phase, short delay, short restore_phase)
{
	int i,j, temp = 0, last_phase;
	if(phase < 0 || phase >= g_phase_num)
	{
		printf("------phase param error %d------\n", phase);
		return ;
	}
	
	switch(mode)
	{
		//stay phase
		case 1:
		//	change_phase(phase);
			break;
		//delay phase
		case 2:
			printf("------delay phase------\n");
			for(i = 0; i < g_light_num; i++)
			{
				trafficlight[i].last_time += delay;
			}
			light_phase[g_phase_no].time_count += delay;
			g_delay_flag = 1;
			break;
		//cut phase
		case 3:
			printf("------cut phase------\n");
			light_phase[g_phase_no].time_count = light_phase[g_phase_no].last_time;
			if(phase == 0)
				phase = g_phase_num -1;
			else
				phase--;
			printf("cut phase %d\n", phase);
			change_phase(0,phase,g_phase_no, 0);
			break;
		//insert phase
		case 4:
			if(phase >= 0 && phase < g_phase_num)
				printf("------insert phase------%d\n", phase);
			else
			{
				printf("------insert phase error------%d\n", phase);
				return ;
			}
			g_insert_phase_flag = 1;
			set_timer(OFF, 500);
			//保存当前相位时间
			g_insert_phase = g_phase_no;
 			g_restore_phase = g_phase_no;
 			g_restore_time = light_phase[g_phase_no].time_count;
 			//when current phase is green,restore phase and time is diffrent from yellow.
 			last_phase = g_phase_no;
			if(light_phase[g_phase_no].cur_status == green)
			{	//if current phase is green,first change yellow,then insert phase.
				g_phase_no++;
				if(g_phase_no >= g_phase_num)
					g_phase_no = 0;
				
				change_phase(1, g_phase_no, last_phase, phase);
			}
			else
			{
				//if current phase is yellow,first run finished,then insert phase.
				calc_last_time(1, g_phase_no, last_phase, phase);
			}
			last_phase = g_phase_no;
			printf("------restore:phase %d, time:%d\n", g_restore_phase, g_restore_time);
			set_timer(ON, 500);
			//等待黄灯运行完
			g_yellow_light = 1;
			while(light_phase[g_phase_no].cur_status == yellow && g_yellow_light)
				usleep(1000);
			
			change_phase(2, phase, last_phase, 0);
			break;
			
		//restore
		case 5:
			if(g_restore_phase >= 0 && g_restore_phase < g_phase_num)
				printf("------restore phase------%d\n", g_restore_phase);
			else
			{
				printf("------restore phase error------%d\n", g_restore_phase);
				return ;
			}
			g_insert_phase_flag = 0;
			set_timer(OFF, 500);
			
			g_phase_no++;
			if(g_phase_no >= g_phase_num)
				g_phase_no = 0;
			
			//when restore,change yellow,then restore phase.
			change_phase(3,g_phase_no,restore_phase, g_restore_phase);
			g_yellow_light = 1;
			while(light_phase[g_phase_no].cur_status == yellow && g_yellow_light)
				usleep(1000);
			
			//last time is enough,restore restore phase,else restore next phase.
			if(g_restore_time > TSP_RESTORE_TIME) {
				change_phase(4,g_restore_phase, g_phase_no, 0);
			}else {
				if(g_restore_phase % 2)
					change_phase(0,g_restore_phase+1, g_phase_no, 0);
				else
					change_phase(0,g_restore_phase+2, g_phase_no, 0);
			}
			tflight_ctrl_info.priority_ctrl_ongoing = 0;
			g_run_time = 0;
			break;
			
	}
}

static void trafficlight_work()
{
	int i, next_phase, len;
	int temp = 0;
#if 1
	if(timer_count == 0)
	{
		timer_count = 1;
		return ;
	}
#endif
	if (timer_count % 2 == 0) 
	{
		light_phase[g_phase_no].time_count--;
		g_run_time++;
	}
	
	for(i = 0; i < g_light_num; i++)
	{
		if(timer_count % 2 == 1)
		{
			if(trafficlight[i].cur_status == green && trafficlight[i].last_time <= 3)
			{
				if(g_delay_flag != 1)
				{
					trafficlight_controlling(i, trafficlight[i].cur_status, OFF);
					write(hc595_fd, light_status, 6);
					printf("count =======%d\n", timer_count);
				}
				else
					g_delay_flag = 0;
			}
			
			if(trafficlight[i].cur_status == yellow)
			{
				for(int j = 0; j < trafficlight[i].num; j++)
				{
					if(trafficlight[i].to[j] == pedestrian)
					{
						trafficlight_write(trafficlight[i].dir[j], trafficlight[i].to[j], green, ON);
						write(hc595_fd, light_status, 6);
					}
				}
			}
			continue;
		}
		else
		{
			if(trafficlight[i].cur_status == green && trafficlight[i].last_time <= 3 && light_phase[g_phase_no].time_count != 0)
			{
				trafficlight_controlling(i, trafficlight[i].cur_status, ON);
				write(hc595_fd, light_status, 6);
				printf("count =======%d\n", timer_count);
			}
			
			if(trafficlight[i].cur_status == yellow && light_phase[g_phase_no].time_count != 0)
			{
				for(int j = 0; j < trafficlight[i].num; j++)
				{
					if(trafficlight[i].to[j] == pedestrian)
					{
						trafficlight_write(trafficlight[i].dir[j], trafficlight[i].to[j], green, OFF);
						write(hc595_fd, light_status, 6);
					}
				}
			}
		}
		if(trafficlight[i].workmode == NORMAL)
			trafficlight[i].last_time--;
		
	}
	timer_count++;
	//插入自动恢复正常
	if(light_phase[g_phase_no].time_count == 0)
	{
		if(g_yellow_light)
		{
			g_yellow_light = 0;
			return;
		}
		
		if(g_insert_phase_flag)
		{
			if(light_phase[g_phase_no].cur_status  == green)
			{
				g_phase_no ++;
				if( g_phase_no >= g_phase_num)
					g_phase_no = 0;
					
				change_phase(3, g_phase_no, 0, g_restore_phase);
			}
			else
			{
				if(g_restore_time > TSP_RESTORE_TIME) {
					change_phase(4,g_restore_phase, g_phase_no, 0);
				}else {
					if(g_restore_phase % 2)
						change_phase(0,g_restore_phase+1, g_phase_no, 0);
					else
						change_phase(0,g_restore_phase+2, g_phase_no, 0);
				}
				tflight_ctrl_info.priority_ctrl_ongoing = 0;
				g_insert_phase_flag = 0;
			}	
		}
		else
		{
			g_phase_no++;
			if(g_phase_no >= g_phase_num)
				g_phase_no = 0;
			change_phase(0, g_phase_no, g_phase_no-1, 0);	
		}
	}
	
	if(timer_count % 2 == 1 && timer_count > 1)
	{
		print_trafficlight();
		pthread_mutex_unlock(&tl_mutex_lock);
	}
}

static void init_sigaction()
{
	sigset_t sigset;
	signal(SIGALRM, trafficlight_work);
	
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGALRM);
	pthread_sigmask(SIG_SETMASK,&sigset,NULL);
}

void trafficlight_write(Direction dir, Toward to, LightType light, char value)
{
	int result, move_result;
	
	result = dir * 4 * 3 + to * 3 + light;
	move_result = (result / 8 + 1) * 8 - 1 - result;
	
	if(value == OFF)
		light_status[result/8] &= ~(1<<(move_result % 8));
	else 
	 	light_status[result/8] |= 1<<(move_result % 8);
	 	
}

//相位配置信息，得出红绿黄周期
void trafficlight_config(TrafficLight_Phase *light_phase, TrafficLight *light, int num)
{
	int i, j = 0, k, red_time = 0;
	//根据相位信息生成红绿灯信息
	for(i = 0; i < num; i++)
	{
		if(light_phase[i].cur_status == green)
		{
			light[g_light_num].dir[0] = light_phase[i].dir;
			light[g_light_num].to[0] = light_phase[i].to;
			light[g_light_num].cur_status = light_phase[i].cur_status;
			light[g_light_num].next_status = light_phase[i].cur_status ? light_phase[i].cur_status-1 : red ;
			light[g_light_num].last_time = light_phase[i].last_time;
			light[g_light_num].regular_light_period[green] = light_phase[i].last_time;
			g_light_num++;
		}
	}
	
	for(i = 0; i < g_light_num; i++)
		for(j = 0; j < num; j++)
		{
			if(light[i].dir[0] == light_phase[j].dir && light[i].to[0] == light_phase[j].to && light_phase[j].cur_status == yellow)
				light[i].regular_light_period[yellow] = light_phase[j].last_time;
		}
		
	for(k = 0, j = 0; j < num; j++)
	{
		red_time = 0;	
		if(light_phase[j].cur_status == green)
		{
			k = j + 2;
			if(k >= num)
				k = 0;
			while(k != j)
			{

				red_time += light_phase[k].last_time;
				k++;
				if(k >= num)
					k = 0;
			}
				
			printf("red_time:%d \n", red_time);
			for(k = 0; k < g_light_num; k++)
				if(light[k].dir[0] == light_phase[j].dir && (light[k].to[0] == light_phase[j].to))
					light[k].regular_light_period[red] = red_time;
		}
	}
		
	for(i = 0; i < g_light_num; i++)
	{
		printf("%d dir:%d to:%d red:%d green:%d yellow:%d\n", i, light[i].dir[0], light[i].to[0], light[i].regular_light_period[red], light[i].regular_light_period[green], light[i].regular_light_period[yellow]);
	}
		
}


//相位信息，工作模式
void trafficlight_value(int no, int *dir, int *to, int num, int value, int workmode)
{
	int i;
	
	trafficlight[no].num = num;
	trafficlight[no].id = value;
	trafficlight[no].workmode = workmode;
	printf("led %d:num %d id %d workmode %d\n", no, trafficlight[no].num, trafficlight[no].id, trafficlight[no].workmode);
	for(i = 0; i < num; i++)
	{
		trafficlight[no].dir[i] = dir[i];
		trafficlight[no].to[i] = to[i];
		printf("dir %d to %d\n", trafficlight[no].dir[i], trafficlight[no].to[i]);
	}	
	
	
}

//得出每个红绿灯在每个相位的剩余时间
void trafficlight_last_time()
{
	int i, j, k,ret;
	
	for(i = 0; i < g_light_num; i++)
	{
		if(trafficlight[i].workmode != NORMAL)
		{
			continue;
		}
			for(j = 0; j < g_phase_num; j++)
			{
				if((trafficlight[i].id * 2 - 1) == j || (trafficlight[i].id * 2 - 2) == j)
				{
					trafficlight[i].last_time_phase[j] = light_phase[j].last_time;
				}
				else
				{
					k = j;
					ret = 0;
					while(k != (trafficlight[i].id * 2 - 2))
					{
						ret += light_phase[k].last_time;
						k++;
						if(k >= g_phase_num)
							k = 0;
					}
					trafficlight[i].last_time_phase[j] = ret;
				}
			}
	}
	
	for(i = 0; i < g_light_num; i++)
	{
		printf("last time %d: ", i);
		for(j = 0; j < g_phase_num; j++)
			printf("%d ", trafficlight[i].last_time_phase[j]);
		printf("\n");
	}

}

//读交通灯配置
int read_config(int *num)
{
	config_t	tl_cfg;
	config_setting_t *setting;
	const char *str;
	char buf[40];
	int j, last_time, light_num;
	
	config_init(&tl_cfg);

	if(! config_read_file(&tl_cfg, "/home/root/config/trafficlight.cfg"))
	{
		fprintf(stderr, "%s:%d - %s\n", config_error_file(&tl_cfg),
						config_error_line(&tl_cfg), config_error_text(&tl_cfg));
		config_destroy(&tl_cfg);
		return -1;
	}

	if(config_lookup_string(&tl_cfg, "name", &str))
		printf("%s\n", str);
	else
		fprintf(stderr, "No 'name' setting in configuration file.\n");
		
	if(config_lookup_string(&tl_cfg, "ip_url", &g_ip_url))
		printf("sending ip %s\n", g_ip_url);
	else
		fprintf(stderr, "No 'ip_url' setting in configuration file.\n");
		
	config_lookup_int(&tl_cfg, "crossroad.num", num);
	printf("trafficlight phase %d\n", *num);
	//读相位配置
	for(j = 0; j < *num; j++)
	{
	
		sprintf(buf, "crossroad.phase%d", j);
		setting = config_lookup(&tl_cfg, buf);
		
	  if(setting != NULL)
	  {
	    int count = config_setting_length(setting);
	    int i;
			printf("count %d\n", count);
	    for(i = 0; i < count; ++i)
	    {
	      config_setting_t *light = config_setting_get_elem(setting, i);

	      /* Only output the record if all of the expected fields are present. */
	      const char *dir, *to, *status;
	      int red_time, green_time, yellow_time, dir_num;
	      if(!(config_setting_lookup_string(light, "dir", &dir)
	           && config_setting_lookup_string(light, "to", &to)
	         //  && config_setting_lookup_int(light, "workmode", &workmode)
	           && config_setting_lookup_string(light, "status", &status)
	           && config_setting_lookup_int(light, "last_time", &last_time)
	        //   && config_setting_lookup_int(light, "num", &dir_num)
	           ))
	        continue;
				
				if(strcmp(dir, "east") == 0)
					light_phase[j].dir = east;
				else if(strcmp(dir, "south") == 0)
					light_phase[j].dir = south;
				else if(strcmp(dir, "west") == 0)
					light_phase[j].dir = west;
				else if(strcmp(dir, "north") == 0)
					light_phase[j].dir = north;
				
				if(strcmp(to, "front") == 0)
					light_phase[j].to = front;
				else if(strcmp(to, "left") == 0)
					light_phase[j].to = left;
				else if(strcmp(to, "right") == 0)
					light_phase[j].to = right;
				else if(strcmp(to, "pedestrian") == 0)
					light_phase[j].to = pedestrian;
				
				if(strcmp(status, "red") == 0)
					light_phase[j].cur_status = red;
				else if(strcmp(status, "green") == 0)
					light_phase[j].cur_status = green;
				else if(strcmp(status, "yellow") == 0)
					light_phase[j].cur_status = yellow;
				
				
				light_phase[j].time_count = light_phase[j].last_time = last_time;
			//	light_phase[j].num = dir_num;
				
				printf("dir:%d, to:%d,status:%d,last_time:%d\n", light_phase[j].dir, light_phase[j].to, light_phase[j].cur_status,light_phase[j].last_time);
	    }
	  }
	}

	trafficlight_config(light_phase, trafficlight,*num);

#if 1
	config_lookup_int(&tl_cfg, "trafficlight.num", &light_num);
	regular_light_num = g_light_num;
	printf("regular trafficlight %d\n", regular_light_num);
	//g_light_num = light_num;
	for(j = 0; j < light_num; j++)
	{
	
		sprintf(buf, "trafficlight.light%d", j);
		setting = config_lookup(&tl_cfg, buf);
		
	  if(setting != NULL)
	  {
	    int count = config_setting_length(setting);
	    int i;
			printf("count %d\n", count);
		  
		  const char *dir, *to, *status;
	    int id, k , dir_buf[10], to_buf[10] , direction[6], toward[6], workmode, led_num = -1; 
	    memset(dir_buf, 0, sizeof(dir_buf));
	    memset(to_buf, 0, sizeof(to_buf));
	    for(i = 0; i < count; ++i)
	    {
	      config_setting_t *light = config_setting_get_elem(setting, i);

	      /* Only output the record if all of the expected fields are present. */
	      
	      if(!(config_setting_lookup_int(light, "num", &led_num)
	           && config_setting_lookup_int(light, "id", &id)
	           && config_setting_lookup_int(light, "workmode", &workmode)
	           ))
	        continue;
	     	if(led_num > 0)
	     	{
	     		
	     			for(k = 0; k < led_num; k++)
	     			{
	     				sprintf(dir_buf, "dir%d", k);
	     				sprintf(to_buf, "to%d", k);
	     				
	     				if(!(config_setting_lookup_string(light, dir_buf, &dir)
	     					&& config_setting_lookup_string(light, to_buf, &to)
	     					))
	     		//			break;
	     				printf("dir:%s to:%s %s %s\n", dir_buf, to_buf, dir, to);	
	     				if(strcmp(dir, "east") == 0)
								direction[k] = east;
							else if(strcmp(dir, "south") == 0)
								direction[k] = south;
							else if(strcmp(dir, "west") == 0)
								direction[k] = west;
							else if(strcmp(dir, "north") == 0)
								direction[k] = north;
							
							if(strcmp(to, "front") == 0)
								toward[k] = front;
							else if(strcmp(to, "left") == 0)
								toward[k] = left;
							else if(strcmp(to, "right") == 0)
								toward[k] = right;
							else if(strcmp(to, "pedestrian") == 0)
								toward[k] = pedestrian;
	     			}
	     	}
				
				#if 1
				if(j == g_light_num)
				{
//					trafficlight[j].dir = direction;
//					trafficlight[j].to = toward;
					g_light_num++;
				}
				#endif
	    }
	    trafficlight_value(j, direction, toward, led_num, id, workmode);
	  }
	}
#endif
  return 0;
}

void *tl_controlling_send_pthread(void *arg)
{
	TflightPackage__TflightPB tf_lightPB = TFLIGHT_PACKAGE__TFLIGHT_PB__INIT;
	TflightPackage__TFmessage **tf_message;
	
	char send_buf[512], i, j, len, id;
	void *context = zmq_ctx_new();
	void *pub = zmq_socket(context, ZMQ_PUB);
	int rc = zmq_bind(pub, "tcp://*:8899");
	assert(rc == 0);
	printf("hello zmq\n");
	memset(send_buf, 0 ,sizeof(send_buf));
	tf_message = malloc (sizeof (TflightPackage__TFmessage*) * (regular_light_num));
	
	for(i = 0; i < regular_light_num; i++)
	{
			tf_message[i] = malloc (sizeof (TflightPackage__TFmessage));
			tflight_package__tfmessage__init(tf_message[i]);
	}
	tf_lightPB.msg_type = 0;
	tf_lightPB.n_tf = trafficlight[regular_light_num - 1].id;
	tf_lightPB.tf = tf_message;
	
	tflight_ctrl_info.priority_ctrl_ongoing = 0;
	while(1)
	{
		pthread_mutex_lock(&tl_mutex_lock);
		printf("tl_controlling_send_pthread\n");
		id = 0;
		for(i = 0, j = 0; i < regular_light_num; i++)
		{
			if(id == trafficlight[i].id)
				continue;
				
			id = trafficlight[i].id;
			tf_message[j]->stage = trafficlight[i].id;
			tf_message[j]->state = trafficlight[i].cur_status;
			if(tf_message[j]->state == red)
				tf_message[j]->state = 'R';
			else if(tf_message[j]->state == green)
				tf_message[j]->state = 'G';
			else
				tf_message[j]->state = 'Y';
			tf_message[j]->time = trafficlight[i].last_time;
			tf_message[j]->nextstate = trafficlight[i].next_status;
			tf_message[j]->nexttime =  trafficlight[i].regular_light_period[ trafficlight[i].next_status];
			tf_message[j]->r_period = trafficlight[i].regular_light_period[red];
			tf_message[j]->g_period = trafficlight[i].regular_light_period[green];
			tf_message[j]->y_period = trafficlight[i].regular_light_period[yellow];
			j++;
		}
		tflight_package__tflight_pb__pack(&tf_lightPB, send_buf);
		len = tflight_package__tflight_pb__get_packed_size(&tf_lightPB);
		zmq_send(pub, send_buf, len ,0);

		#if 1
		tflight_ctrl_info.msg_type = 3;
		tflight_ctrl_info.curr_light_phase =  g_phase_no + 1;
		tflight_ctrl_info.curr_light_state = light_phase[g_phase_no].cur_status;
		if(tflight_ctrl_info.curr_light_state == red)
			tflight_ctrl_info.curr_light_state = 'R';
		else if(tflight_ctrl_info.curr_light_state == green)
			tflight_ctrl_info.curr_light_state = 'G';
		else
			tflight_ctrl_info.curr_light_state = 'Y';
			
		tflight_ctrl_info.curr_run_time = g_run_time + 1;
		if(tflight_ctrl_info.priority_ctrl_ongoing == 1 && tflight_ctrl_info.curr_light_state == 'G' && light_phase[g_phase_no].last_time == 0)
			tflight_ctrl_info.priority_ctrl_ongoing = 0;
//		printf("msg_type %d\n", tflight_ctrl_info.msg_type);
		tflight_package__tflight_ctrl_info__pack(&tflight_ctrl_info, send_buf);
		len = tflight_package__tflight_ctrl_info__get_packed_size(&tflight_ctrl_info);
		zmq_send(pub, send_buf, len ,0);
		#endif
		//usleep(700*1000);	
	}
	for(i = 0; i < g_light_num; i++)
		free(tf_message[i]);
	
	pthread_mutex_destroy(&tl_mutex_lock);
	free(tf_message);
	zmq_close(pub);
	zmq_ctx_destroy(context);
}

void *tl_controlling_recv_pthread(void *arg)
{
	char buf[200], recv_num;
	struct timeval start;
	struct timeval end;
	int interval_time;
	TspFunctionType last_rule, cur_rule;
	TflightPackage__BaseMsg *base_msg;
	TflightPackage__ServCtrlInfo *ctrl_info;
	void *context = zmq_ctx_new();
	void *sub = zmq_socket(context, ZMQ_SUB);
	
	int rc = zmq_connect(sub, g_ip_url);
	assert(rc == 0);
	
	rc = zmq_setsockopt(sub, ZMQ_SUBSCRIBE, "", 0);
	assert(rc == 0);
	memset(buf, 0, sizeof(buf));
	gettimeofday(&start, NULL);
	last_rule = kNormal;
	cur_rule = kNormal;
	
	while(1)
	{
		recv_num = zmq_recv(sub, buf, 200, 0);
//		printf("responder recv: %d\n", recv_num);
		base_msg =  tflight_package__base_msg__unpack(NULL, recv_num, buf);
		if(base_msg == NULL)
		{
			continue;
		}
		
		switch(base_msg->msg_type)
		{
			case 4:
				gettimeofday(&end, NULL);
				interval_time = end.tv_sec - start.tv_sec;
				printf("interval time: %d\n", interval_time);
				ctrl_info = tflight_package__serv_ctrl_info__unpack(NULL, recv_num, buf);
				printf("mode: %d,priority_rule:%d,curr_phase:%d,green_extend_time:%d,restore_phase:%d\n",\
							ctrl_info->mode, ctrl_info->priority_rule,ctrl_info->curr_vehicle_phase,ctrl_info->green_extend_time,ctrl_info->restore_phase);
				cur_rule = ctrl_info->priority_rule;
				printf("last rule:%d, cur rule:%d\n", last_rule, cur_rule);
				
				//TSP CONTROLL interval time
				if(((last_rule == kDelay) || (last_rule == kCut) || (last_rule == kRestore)) && (cur_rule > kNormal) &&  (interval_time < TSP_CONTROLL_INTERVAL_TIME))
					break;
				
				if((last_rule == kInsert) && (cur_rule != kRestore) && (interval_time < TSP_CONTROLL_INTERVAL_TIME) )
					break;
				
				if((last_rule == kInsert) && (cur_rule == kRestore) && (interval_time < TSP_CONTROLL_RESTORE_INTERVAL_TIME) )
					break;
				

				gettimeofday(&start, NULL);
				tflight_ctrl_info.priority_ctrl_ongoing = 1;	
				last_rule = cur_rule;
				TSP_controlling(ctrl_info->priority_rule, ctrl_info->curr_vehicle_phase - 1, ctrl_info->green_extend_time, ctrl_info->restore_phase - 1);
				
				break;
				
			default:
				break;
		}
	}
	zmq_close(sub);
	zmq_ctx_destroy(context);
}


int trafficlight_init()
{
	int i,j;
	pthread_t tid_sub, tid_pub;
	
	pthread_mutex_init(&tl_mutex_lock, NULL);
	pthread_mutex_lock(&tl_mutex_lock);
	hc595_fd = open("/dev/hc595", O_RDWR, S_IRUSR|S_IWUSR);
	if(hc595_fd == -1)
	{
		printf("can't open hc595\n");
		return -1;
	}
	memset(light_status, 0xff, sizeof(light_status));
	
	for(i = 0; i < 3; i++)
	{
		usleep(500*1000);
		light_status[0] = 0xff;
		light_status[1] = 0xff;
		light_status[2] = 0xff;
		light_status[3] = 0xff;
		light_status[4] = 0xff;
		light_status[5] = 0xff;
		write(hc595_fd, light_status, 6);
		
		usleep(500*1000);
		light_status[0] = 0x00;
		light_status[1] = 0x00;
		light_status[2] = 0x00;
		light_status[3] = 0x00;
		light_status[4] = 0x00;
		light_status[5] = 0x00;
		write(hc595_fd, light_status, 6);
	}
			
	read_config(&g_phase_num);

	trafficlight_last_time();

	pthread_create(&tid_pub,NULL,tl_controlling_send_pthread, NULL);
	pthread_create(&tid_sub,NULL,tl_controlling_recv_pthread, NULL);
	init_sigaction();
	change_phase(0,0,0,0);

	for(i = 0; i < g_light_num; i++)
	{
		printf("-------workmode %d\n", trafficlight[i].workmode);
		if(trafficlight[i].workmode == ONLINEG)
		{
			trafficlight[i].cur_status = green;
			trafficlight_controlling(i, green, ON);
		}
	}
	write(hc595_fd, light_status, 6);

	return tid_pub;
}
