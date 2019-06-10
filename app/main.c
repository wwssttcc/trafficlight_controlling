#include <stdio.h>
#include <stdlib.h>
#include "tl_tcpserver.h"
#include"tl_controlling.h"

int main(int argc, char **argv)
{
	 pthread_t tcp_tid, tl_tid;
	//printf("trafficlight controlling v1.0\n");
	//tcp_tid = tl_tcpserver_init();
	tl_tid = trafficlight_init();
	
	//pthread_join(tcp_tid, NULL);
	pthread_join(tl_tid, NULL);
	while(1);
	return 0;
}