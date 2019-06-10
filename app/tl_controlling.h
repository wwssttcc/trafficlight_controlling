#ifndef _TL_CONTROLLING_H_
#define _TL_CONTROLLING_H_


typedef enum LightType{
	yellow = 0,
	green,
	red,
//	unknown,
}LightType;

typedef enum Direction{
	north = 0,
	south,
	west,
	east,
}Direction;

typedef enum Toward{
	pedestrian = 0,
	right,
	front,
	left,
	
}Toward;

typedef struct TrafficLight{
	Direction	dir;
	Toward	to;
	char id;
	LightType	cur_status;
	LightType	next_status;
	unsigned short last_time;
	unsigned short regular_light_period[3];
	unsigned short special_light_period[3];
	unsigned short last_time_phase[12];
	unsigned char workmode;
}TrafficLight;

typedef struct TrafficLight_Phase{
	Direction	dir;
	Toward	to;
	LightType	cur_status;
	unsigned short last_time;
	unsigned short time_count;
	unsigned short run_time;
	unsigned char workmode;
	unsigned char num;
}TrafficLight_Phase;

int trafficlight_init();
void TSP_controlling(char mode, char phase, char delay, char restore_phase);
#endif