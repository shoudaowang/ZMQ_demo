#include "bug_zmq.h"
#include <windows.h>
//#include "log.h"
#include <stdarg.h>
#include <atltrace.h>
using namespace ATL;
   
DWORD WINAPI ZmqWorker()
{

	void*	context		=	zmq_ctx_new();
	void*	z_socket	=	zmq_socket(context,ZMQ_REP);
	int		rc			=	zmq_bind(z_socket,"tcp://*:5555");
    
    int j = 1;
	while(1)
	{
        
		zmq_msg_t recv_msg;
		int rc = zmq_msg_init(&recv_msg);
		rc = zmq_msg_recv(&recv_msg,z_socket,ZMQ_DONTWAIT);
        
		//没有收到消息
		if(rc == -1) 
		{
			Sleep(1);
			continue;


		}

		char* data;
		data = (char*)zmq_msg_data(&recv_msg);
        printf("接收到消息length：%d %s\r\n 第%d次 \r\n",rc,data,j);
        int result = zmq_msg_close(&recv_msg);
        printf("zmq_msg_close结束result：%d  第%d次 \r\n",result,j);

        zmq_msg_t send_msg;
		zmq_msg_init_size(&send_msg,3);
        memcpy(zmq_msg_data(&send_msg),"ok",3);
		result = zmq_sendmsg(z_socket,&send_msg,NULL);
        printf("zmq_sendmsg结束result：%d  第%d次 \r\n",result,j);
        result = zmq_msg_close(&send_msg);
        printf("zmq_msg_close结束result：%d  第%d次 \r\n",result,j);
        j++;
	}

	int close = zmq_close(z_socket);
    printf("close :%d\n",close);
	zmq_ctx_shutdown(context);


	return NULL;
}


int main(){
   ZmqWorker();
} 

