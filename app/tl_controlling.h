#ifndef _TL_CONTROLLING_H_
#define _TL_CONTROLLING_H_

#define NORMAL	1
#define ONLINEG	2

#define TSP_CONTROLL_INTERVAL_TIME	40
#define TSP_CONTROLL_RESTORE_INTERVAL_TIME	4
#define TSP_RESTORE_TIME 10

typedef enum TspFunctionType {
	kNormal = 1,
	kDelay,
	kCut,
	kInsert,
	kRestore,
}TspFunctionType;

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
	unsigned char num;
	Direction	dir[6];
	Toward	to[6];
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
}TrafficLight_Phase;

int trafficlight_init();
void TSP_controlling(char mode, short phase, short delay, short restore_phase);
#endif
