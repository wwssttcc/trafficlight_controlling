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
#include"tl_controlling.h"
#include "include/libconfig.h"
#include"tl_message.pb-c.h"
#include "zmq.h"

#define ON	1
#define OFF	0

static int hc595_fd;
static unsigned char light_status[6];

static unsigned int timer_count = 0;
static TrafficLight trafficlight[16];
static TrafficLight_Phase light_phase[8];
static int g_light_num = 0;
static int g_phase_num = 0;
static int g_phase_no = 0;
static char g_yellow_light = 0;
static char g_send_buf[200];
static char *g_ip_url;
static int g_run_time = 0;
static char g_restore_phase = -1;
TflightPackage__TFLightCtrlInfo tflight_ctrl_info = TFLIGHT_PACKAGE__TFLIGHT_CTRL_INFO__INIT;

static void trafficlight_write(Direction dir, Toward to, LightType light, char value);

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

void change_phase(char no)
{
	int i;
	
	memset(light_status, 0, sizeof(light_status));
	set_timer(OFF, 500);
	g_run_time = 0;
	write(hc595_fd, light_status, sizeof(light_status));
	for(i = 0; i < g_light_num; i++)
	{
		if((trafficlight[i].dir == light_phase[no].dir || trafficlight[i].dir == (light_phase[no].dir - 1)) && (trafficlight[i].to == light_phase[no].to))
			{
				trafficlight[i].cur_status = light_phase[no].cur_status;
				trafficlight[i].next_status = trafficlight[i].cur_status ? trafficlight[i].cur_status -1 : red;
				trafficlight[i].last_time = light_phase[no].last_time;
				trafficlight_write(trafficlight[i].dir, trafficlight[i].to, trafficlight[i].cur_status, ON);
			}
			else
			{
				trafficlight[i].cur_status = red;
				trafficlight[i].next_status = trafficlight[i].cur_status ? trafficlight[i].cur_status -1 : red;
				trafficlight[i].last_time = trafficlight[i].last_time_phase[no];
				trafficlight_write(trafficlight[i].dir, trafficlight[i].to, red, ON);
			}
	}
	g_phase_no = no;
	set_timer(ON, 500);
}


void TSP_controlling(char mode, char phase, char delay, char restore_phase)
{
	int i,j;
	static char g_restore_time[12];
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
			break;
		//cut phase
		case 3:
			printf("------cut phase------\n");
			phase--;
			if(phase < 0)
				phase = g_phase_num -1;
				
			change_phase(phase);
			break;
		//insert phase
		case 4:
			printf("------insert phase------\n");
			set_timer(OFF, 500);
			for(i = 0; i < g_light_num; i++)
			{
				g_restore_time[i] = trafficlight[i].last_time;
			}
			g_restore_phase = g_phase_no;
			g_phase_no++;
			if(g_phase_no >= g_phase_num)
				g_phase_no = 0;
			
			change_phase(g_phase_no);
			while(light_phase[g_phase_no].cur_status == yellow)
				usleep(1000);
			change_phase(phase);
			break;
		//restore
		case 5:
			printf("------restore phase------\n");
			g_phase_no++;
			if(g_phase_no >= g_phase_num)
				g_phase_no = 0;
			
			change_phase(g_phase_no);
			while(light_phase[g_phase_no].cur_status == yellow)
				usleep(1000);
				
			change_phase(restore_phase);
			if(g_restore_phase == restore_phase)
			{
				g_phase_no = restore_phase;
				for(i = 0; i < g_light_num; i++)
				{
					trafficlight[i].last_time = g_restore_time[i];
				}
			}
				
			g_run_time = 0;
			tflight_ctrl_info.priority_ctrl_ongoing = 0;
			break;
			
	}
}

static void trafficlight_work()
{
	int i, next_phase, len;
	
	timer_count++;

	if (timer_count % 2 == 0) 
	{
		light_phase[g_phase_no].time_count--;
		g_run_time++;
		printf("phase: %d  last_time: %d run_time: %d\n", g_phase_no, light_phase[g_phase_no].time_count, g_run_time);
	}
	
	for(i = 0; i < g_light_num; i++)
	{
		if(timer_count % 2 == 1)
		{
			if(trafficlight[i].cur_status == yellow)
			{
				trafficlight_write(trafficlight[i].dir, trafficlight[i].to, trafficlight[i].cur_status, OFF);
			}
			continue;
		}
		else
		{
			if(trafficlight[i].cur_status == yellow)
			{
				trafficlight_write(trafficlight[i].dir, trafficlight[i].to, trafficlight[i].cur_status, ON);
			}
		}
		trafficlight[i].last_time--;
		printf("No %d: ", i+1);
		switch(trafficlight[i].dir)
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
		
		switch(trafficlight[i].to)
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
		if(light_phase[g_phase_no].time_count == 0)
		{
			next_phase = g_phase_no + 1;
			if(next_phase >= g_phase_num)
				next_phase = 0;
			
			if((trafficlight[i].dir == light_phase[g_phase_no].dir || trafficlight[i].dir == (light_phase[g_phase_no].dir - 1)) && (trafficlight[i].to == light_phase[g_phase_no].to))
			{
				trafficlight_write(trafficlight[i].dir, trafficlight[i].to, trafficlight[i].cur_status, OFF);
				trafficlight[i].cur_status =  trafficlight[i].cur_status ? trafficlight[i].cur_status -1 : red;
				trafficlight[i].next_status = trafficlight[i].cur_status ? trafficlight[i].cur_status -1 : red;
				trafficlight[i].last_time = trafficlight[i].regular_light_period[trafficlight[i].cur_status];
				trafficlight_write(trafficlight[i].dir, trafficlight[i].to, trafficlight[i].cur_status, ON);
			}
			
			if((trafficlight[i].dir == light_phase[next_phase].dir || trafficlight[i].dir == (light_phase[next_phase].dir - 1)) && (trafficlight[i].to == light_phase[next_phase].to))
			{
				trafficlight_write(trafficlight[i].dir, trafficlight[i].to, trafficlight[i].cur_status, OFF);
				trafficlight[i].cur_status = light_phase[next_phase].cur_status;
				trafficlight[i].next_status = trafficlight[i].cur_status ? trafficlight[i].cur_status -1 : red;
				trafficlight[i].last_time = light_phase[next_phase].last_time;
				trafficlight_write(trafficlight[i].dir, trafficlight[i].to, trafficlight[i].cur_status, ON);
			}
			
			#if 0
			else
			{
				trafficlight[i].cur_status = red;
				trafficlight[i].next_status = trafficlight[i].cur_status ? trafficlight[i].cur_status -1 : red;
				trafficlight[i].last_time = trafficlight[i].regular_light_period[red];
				trafficlight_write(trafficlight[i].dir, trafficlight[i].to, red, ON);
			}
			#endif
			if(i == (g_light_num - 1))
			{
				g_run_time = 0;
				light_phase[g_phase_no].time_count = light_phase[g_phase_no].last_time;
				g_phase_no++;
				if(g_phase_no >= g_phase_num)
					g_phase_no = 0;
			}
		
		}
		
	}
	
	printf("---------trafficlight work---------\n");
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
	 	
	write(hc595_fd, light_status, 6);
}

void trafficlight_config(TrafficLight_Phase *light_phase, TrafficLight *light, int num)
{
	int i, j = 0, k, red_time = 0;;
	for(i = 0; i < num; i++)
	{
		if(light_phase[i].cur_status == green)
		{
			for(j = 0; j < light_phase[i].num; j++)
			{
				light[g_light_num].dir = light_phase[i].dir - j;
				light[g_light_num].to = light_phase[i].to;
				light[g_light_num].workmode = light_phase[i].workmode;
				light[g_light_num].cur_status = light_phase[i].cur_status;
				light[g_light_num].next_status = light_phase[i].cur_status ? light_phase[i].cur_status-1 : red ;
				light[g_light_num].last_time = light_phase[i].last_time;
				light[g_light_num].regular_light_period[green] = light_phase[i].last_time;
				g_light_num++;
			}
		}
	}
	
	for(i = 0; i < g_light_num; i++)
		for(j = 0; j < num; j++)
		{
			if((light[i].dir == light_phase[j].dir || light[i].dir == (light_phase[j].dir - 1)) && light[i].to == light_phase[j].to && light_phase[j].cur_status == yellow)
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
				if((light[k].dir == light_phase[j].dir || light[k].dir == (light_phase[j].dir - 1)) && (light[k].to == light_phase[j].to))
					light[k].regular_light_period[red] = red_time;
		}
	}
		
	for(i = 0; i < g_light_num; i++)
	{
		printf("%d dir:%d to:%d red:%d green:%d yellow:%d\n", i, light[i].dir, light[i].to, light[i].regular_light_period[red], light[i].regular_light_period[green], light[i].regular_light_period[yellow]);
	}
		
}

void trafficlight_value(int dir, int to, int value)
{
	int i;
	
	for(i = 0; i < g_light_num; i++)
	{
		if(trafficlight[i].dir == dir && trafficlight[i].to == to)
		{
			trafficlight[i].id = value;
		}
	}
	
}

void trafficlight_last_time()
{
	int i, j, k,ret;
	
	for(i = 0; i < g_light_num; i++)
	{
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

int read_config(int *num)
{
	config_t	tl_cfg;
	config_setting_t *setting;
	const char *str;
	char buf[40];
	int j, last_time, light_num;
	
	config_init(&tl_cfg);

	if(! config_read_file(&tl_cfg, "/home/root/trafficlight.cfg"))
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
	      int workmode, red_time, green_time, yellow_time, dir_num;
	      if(!(config_setting_lookup_string(light, "dir", &dir)
	           && config_setting_lookup_string(light, "to", &to)
	           && config_setting_lookup_int(light, "workmode", &workmode)
	           && config_setting_lookup_string(light, "status", &status)
	           && config_setting_lookup_int(light, "last_time", &last_time)
	           && config_setting_lookup_int(light, "num", &dir_num)
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
				
				
				light_phase[j].workmode = workmode;
				light_phase[j].time_count = light_phase[j].last_time = last_time;
				light_phase[j].num = dir_num;
				
				printf("g_phase_num:%d,dir:%d, to:%d,workmode:%d,status:%d,last_time:%d\n", light_phase[j].num,\
				light_phase[j].dir, light_phase[j].to, light_phase[j].cur_status, light_phase[j].workmode,light_phase[j].last_time \
				);
	    }
	  }
	}

	trafficlight_config(light_phase, trafficlight,*num);
#if 1
  config_lookup_int(&tl_cfg, "trafficlight.num", &light_num);
	printf("trafficlight %d\n", light_num);
	
	for(j = 0; j < light_num; j++)
	{
	
		sprintf(buf, "trafficlight.light%d", j);
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
	      int id, direction, toward;
	      if(!(config_setting_lookup_string(light, "dir", &dir)
	           && config_setting_lookup_string(light, "to", &to)
	           && config_setting_lookup_int(light, "id", &id)
	           ))
	        continue;
				
				if(strcmp(dir, "east") == 0)
					direction = east;
				else if(strcmp(dir, "south") == 0)
					direction = south;
				else if(strcmp(dir, "west") == 0)
					direction = west;
				else if(strcmp(dir, "north") == 0)
					direction = north;
				
				if(strcmp(to, "front") == 0)
					toward = front;
				else if(strcmp(to, "left") == 0)
					toward = left;
				else if(strcmp(to, "right") == 0)
					toward = right;
				else if(strcmp(to, "pedestrian") == 0)
					toward = pedestrian;
				
				trafficlight_value(direction, toward, id);
				//printf("id %d\n", id);
	    }
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
	tf_message = malloc (sizeof (TflightPackage__TFmessage*) * (g_light_num));
	
	for(i = 0; i < g_light_num; i++)
	{
			tf_message[i] = malloc (sizeof (TflightPackage__TFmessage));
			tflight_package__tfmessage__init(tf_message[i]);
	}
	tf_lightPB.msg_type = 0;
	tf_lightPB.n_tf = trafficlight[g_light_num - 1].id;
	tf_lightPB.tf = tf_message;
	
	tflight_ctrl_info.priority_ctrl_ongoing = 0;
	while(1)
	{
		id = 0;
		for(i = 0, j = 0; i < g_light_num; i++)
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
		tflight_ctrl_info.msg_type = 2;
		tflight_ctrl_info.curr_light_phase =  g_phase_no + 1;
		tflight_ctrl_info.curr_light_state = light_phase[g_phase_no].cur_status;
		if(tflight_ctrl_info.curr_light_state == red)
			tflight_ctrl_info.curr_light_state = 'R';
		else if(tflight_ctrl_info.curr_light_state == green)
			tflight_ctrl_info.curr_light_state = 'G';
		else
			tflight_ctrl_info.curr_light_state = 'Y';
			
		tflight_ctrl_info.curr_run_time = g_run_time;
		if(tflight_ctrl_info.priority_ctrl_ongoing == 1 && tflight_ctrl_info.curr_light_state == 'G' && light_phase[g_phase_no].last_time == 0)
			tflight_ctrl_info.priority_ctrl_ongoing = 0;
		tflight_package__tflight_ctrl_info__pack(&tflight_ctrl_info, send_buf);
		len = tflight_package__tflight_ctrl_info__get_packed_size(&tflight_ctrl_info);
		zmq_send(pub, send_buf, len ,0);
		#endif
		usleep(700*1000);	
	}
	for(i = 0; i < g_light_num; i++)
		free(tf_message[i]);
		
	free(tf_message);
	zmq_close(pub);
	zmq_ctx_destroy(context);
}

void *tl_controlling_recv_pthread(void *arg)
{
	char buf[200], recv_num;
	TflightPackage__BaseMsg *base_msg;
	TflightPackage__ServCtrlInfo *ctrl_info;
	void *context = zmq_ctx_new();
	void *sub = zmq_socket(context, ZMQ_SUB);
	
	int rc = zmq_connect(sub, g_ip_url);
	assert(rc == 0);
	
	rc = zmq_setsockopt(sub, ZMQ_SUBSCRIBE, "", 0);
	assert(rc == 0);
	memset(buf, 0, sizeof(buf));
	while(1)
	{
		recv_num = zmq_recv(sub, buf, 200, 0);
		printf("responder recv:\n");
		base_msg =  tflight_package__base_msg__unpack(NULL, recv_num, buf);
		if(base_msg == NULL)
		{
			continue;
		}
		
		switch(base_msg->msg_type)
		{
			case 3:
				ctrl_info = tflight_package__serv_ctrl_info__unpack(NULL, recv_num, buf);
				printf("mode: %d,priority_rule:%d,curr_phase:%d,green_extend_time:%d,restore_phase:%d\n",\
							ctrl_info->mode, ctrl_info->priority_rule,ctrl_info->curr_vehicle_phase,ctrl_info->green_extend_time,ctrl_info->restore_phase);
				TSP_controlling(ctrl_info->priority_rule, ctrl_info->curr_vehicle_phase - 1, ctrl_info->green_extend_time, ctrl_info->restore_phase - 1);
				tflight_ctrl_info.priority_ctrl_ongoing = 1;	
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
		light_status[0] = 0x00;
		light_status[1] = 0x00;
		light_status[2] = 0x00;
		light_status[3] = 0x00;
		light_status[4] = 0x00;
		light_status[5] = 0x00;
		write(hc595_fd, light_status, 6);

		usleep(500*1000);
		light_status[0] = 0xff;
		light_status[1] = 0xff;
		light_status[2] = 0xff;
		light_status[3] = 0xff;
		light_status[4] = 0xff;
		light_status[5] = 0xff;
		write(hc595_fd, light_status, 6);
	}
		
	#if 0
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
		{
			trafficlight_write(i, j, red, ON);
			sleep(1);
			trafficlight_write(i, j, green, ON);
			sleep(1);
			trafficlight_write(i, j, yellow, ON);
			sleep(1);
			if(j == 3)
				break;
		}
	#endif
	
	read_config(&g_phase_num);
	trafficlight_last_time();
#if 0
	for(i = 0; i < g_light_num; i++)
	{
		trafficlight_write(trafficlight[i].dir, trafficlight[i].to, trafficlight[i].cur_status, ON);
	}
#endif
	
	pthread_create(&tid_pub,NULL,tl_controlling_send_pthread, NULL);
	pthread_create(&tid_sub,NULL,tl_controlling_recv_pthread, NULL);
	init_sigaction();
	change_phase(0);

	return tid_pub;
}
