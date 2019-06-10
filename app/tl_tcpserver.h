#ifndef _TL_TCPSERVER_H_
#define _TL_TCPSERVER_H_ 
#include<pthread.h>

#define TL_TCPSERVER_PORT   8899

pthread_t tl_tcpserver_init();
extern int server_sock;
#endif
