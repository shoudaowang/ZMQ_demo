#include "client.h"
using namespace std;
/*
socket和上下文创建要放在循环外，不然会出现丢包和阻塞情况
上下文和套接字会创建并返回句柄
只在开始结束和出错时销毁上下文
zmq_setsockopt要在连接前设置
*/
void SendMsgToAddin()//错误demo
{
    int i =0;
    char* msg="client";
    while(1)
    {
        Sleep(100);
        i++;
	    void* context	= zmq_ctx_new();  //指定zmq 处理I/0事件的thread pool 为1
	    void* z_socket	= zmq_socket(context,ZMQ_REQ);//失败返回NULL
        if(context == NULL )printf ("errrrrrrrrr");
        char recvBuffer[256] = { 0 };
	    int isConnected = zmq_connect(z_socket,"tcp://localhost:5555");//成功返回0
        if(isConnected == 0)
        {
            //string tmp1 = "成功建立连接第"+std::to_string(i)+"次";输出到txt文件用，需要opencv库
            //put_localmac(tmp1);
            printf("成功建立连接第%d次\n", i);
        }

	    memset(recvBuffer, 0, 256);

	    int err = zmq_send(z_socket,msg, strlen(msg) ,0);//阻塞模式，第四个参数为ZMQ_DONTWAIT即非阻塞模式成功返回字节数

        if(err == strlen(msg))
        {
            //string tmp2 = "已发送第"+std::to_string(i)+"次";
            //put_localmac(tmp2);
            printf("已发送第%d次\n", i);
        }



	    int recv = zmq_recv(z_socket, recvBuffer, 3, 0);//阻塞模式，第四个参数为ZMQ_DONTWAIT即非阻塞模式成功返回0
        printf("%d",recv);
        if(recv == 3)
        {
            printf("收到Server端回答第%d次:%s\t\n",i,recvBuffer);
     
        }


    
        zmq_disconnect(z_socket,"tcp://localhost:5555");//去掉后错误率很高
        int close = zmq_close(z_socket);
        printf("close :%d\n",close);
        int destroy = zmq_ctx_destroy(context);
        printf("destroy :%d\n",destroy);
    }
}


void temp()//验证句柄
{
    int i =0;
    char* msg="client";
    while(1)
    {
        Sleep(100);
        i++;
        void* context	= zmq_ctx_new();  
	    void* z_socket	= zmq_socket(context,ZMQ_REQ);
        int isConnected = zmq_connect(z_socket,"tcp://localhost:5555");//成功返回0

            if(isConnected == 0)
            {
                //string tmp1 = "成功建立连接第"+std::to_string(i)+"次";
                //put_localmac(tmp1);
                printf("成功建立连接第%d次\n", i);
            }
        //去掉下面注释后就可实现原demo的错误
        /*
        zmq_send(z_socket,msg, strlen(msg) ,0);//成功返回字节数
        zmq_disconnect(z_socket,"tcp://localhost:5555");//成功返回0
        int close = zmq_close(z_socket);
        printf("close :%d\n",close);
        int destroy = zmq_ctx_destroy(context);//成功返回0
        printf("destroy :%d\n",destroy);
        */
    }

}


void demotrue()//正确demo提出context和socket初始化
{
    void* context	= zmq_ctx_new(); 
	void* z_socket	= zmq_socket(context,ZMQ_REQ);
    int time = 300;
    zmq_setsockopt (z_socket, ZMQ_SNDTIMEO, &time, sizeof(time));
    zmq_setsockopt (z_socket, ZMQ_RCVTIMEO, &time, sizeof(time));
    zmq_setsockopt(z_socket, ZMQ_LINGER,&time, sizeof(time));
    int i =0;
    char* msg="client";
    while(1)
    {
        Sleep(10);

        i++;
        string num="1";
    
        char recvBuffer[256] = { 0 };
	    int isConnected = zmq_connect(z_socket,"tcp://localhost:5555");//成功返回0
        if(isConnected == 0)
        {
            //string tmp1 = "成功建立连接第"+std::to_string(i)+"次";
            //put_localmac(tmp1);
            printf("成功建立连接第%d次\n", i);
        }

	    memset(recvBuffer, 0, 256);

	    int err = zmq_send(z_socket,msg, strlen(msg) ,0);//阻塞模式，第四个参数为ZMQ_DONTWAIT即非阻塞模式成功返回字节数
        if(err == strlen(msg))
        {
            //string tmp2 = "已发送第"+std::to_string(i)+"次";
            //put_localmac(tmp2);
            printf("已发送第%d次\n", i);
        }
        
        //else
        //{
            //zmq_close(z_socket);

            //z_socket	= zmq_socket(context,ZMQ_REQ);
            //int time = 300;
            //zmq_setsockopt (z_socket, ZMQ_SNDTIMEO, &time, sizeof(time));
            //zmq_setsockopt (z_socket, ZMQ_RCVTIMEO, &time, sizeof(time));
            //continue;
        //}
        
	    int recv = zmq_recv(z_socket, recvBuffer, 3, 0);//阻塞模式，第四个参数为ZMQ_DONTWAIT即非阻塞模式成功返回0
        printf("%d",recv);
        if(recv == 3)
        {
            printf("收到Server端回答第%d次:%s\t\n",i,recvBuffer);
     
        }
        else
        {
            printf("recv,err\n");  
            zmq_close(z_socket);
            zmq_ctx_destroy(context);
           
            context = zmq_ctx_new();
            z_socket	= zmq_socket(context,ZMQ_REQ);
            int time = 300;
            zmq_setsockopt (z_socket, ZMQ_SNDTIMEO, &time, sizeof(time));
            zmq_setsockopt (z_socket, ZMQ_RCVTIMEO, &time, sizeof(time));
            zmq_setsockopt(z_socket, ZMQ_LINGER,&time, sizeof(time));
            continue;
        }

        
        //int close = zmq_close(z_socket);
        //printf("close :%d\n",close);

        
    }
    zmq_disconnect(z_socket,"tcp://localhost:5555");
    int close = zmq_close(z_socket);//成功返回0
    printf("close :%d\n",close);
    int destroy = zmq_ctx_destroy(context);//成功返回0
    printf("destroy :%d\n",destroy);

}
int  main()
{
    //temp();//验证句柄增加
    demotrue();//正确demo
    //SendMsgToAddin();//原demo
}