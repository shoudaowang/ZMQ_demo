#include "client.h"
using namespace std;
/*
socket�������Ĵ���Ҫ����ѭ���⣬��Ȼ����ֶ������������
�����ĺ��׽��ֻᴴ�������ؾ��
ֻ�ڿ�ʼ�����ͳ���ʱ����������
zmq_setsockoptҪ������ǰ����
*/
void SendMsgToAddin()//����demo
{
    int i =0;
    char* msg="client";
    while(1)
    {
        Sleep(100);
        i++;
	    void* context	= zmq_ctx_new();  //ָ��zmq ����I/0�¼���thread pool Ϊ1
	    void* z_socket	= zmq_socket(context,ZMQ_REQ);//ʧ�ܷ���NULL
        if(context == NULL )printf ("errrrrrrrrr");
        char recvBuffer[256] = { 0 };
	    int isConnected = zmq_connect(z_socket,"tcp://localhost:5555");//�ɹ�����0
        if(isConnected == 0)
        {
            //string tmp1 = "�ɹ��������ӵ�"+std::to_string(i)+"��";�����txt�ļ��ã���Ҫopencv��
            //put_localmac(tmp1);
            printf("�ɹ��������ӵ�%d��\n", i);
        }

	    memset(recvBuffer, 0, 256);

	    int err = zmq_send(z_socket,msg, strlen(msg) ,0);//����ģʽ�����ĸ�����ΪZMQ_DONTWAIT��������ģʽ�ɹ������ֽ���

        if(err == strlen(msg))
        {
            //string tmp2 = "�ѷ��͵�"+std::to_string(i)+"��";
            //put_localmac(tmp2);
            printf("�ѷ��͵�%d��\n", i);
        }



	    int recv = zmq_recv(z_socket, recvBuffer, 3, 0);//����ģʽ�����ĸ�����ΪZMQ_DONTWAIT��������ģʽ�ɹ�����0
        printf("%d",recv);
        if(recv == 3)
        {
            printf("�յ�Server�˻ش��%d��:%s\t\n",i,recvBuffer);
     
        }


    
        zmq_disconnect(z_socket,"tcp://localhost:5555");//ȥ��������ʺܸ�
        int close = zmq_close(z_socket);
        printf("close :%d\n",close);
        int destroy = zmq_ctx_destroy(context);
        printf("destroy :%d\n",destroy);
    }
}


void temp()//��֤���
{
    int i =0;
    char* msg="client";
    while(1)
    {
        Sleep(100);
        i++;
        void* context	= zmq_ctx_new();  
	    void* z_socket	= zmq_socket(context,ZMQ_REQ);
        int isConnected = zmq_connect(z_socket,"tcp://localhost:5555");//�ɹ�����0

            if(isConnected == 0)
            {
                //string tmp1 = "�ɹ��������ӵ�"+std::to_string(i)+"��";
                //put_localmac(tmp1);
                printf("�ɹ��������ӵ�%d��\n", i);
            }
        //ȥ������ע�ͺ�Ϳ�ʵ��ԭdemo�Ĵ���
        /*
        zmq_send(z_socket,msg, strlen(msg) ,0);//�ɹ������ֽ���
        zmq_disconnect(z_socket,"tcp://localhost:5555");//�ɹ�����0
        int close = zmq_close(z_socket);
        printf("close :%d\n",close);
        int destroy = zmq_ctx_destroy(context);//�ɹ�����0
        printf("destroy :%d\n",destroy);
        */
    }

}


void demotrue()//��ȷdemo���context��socket��ʼ��
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
	    int isConnected = zmq_connect(z_socket,"tcp://localhost:5555");//�ɹ�����0
        if(isConnected == 0)
        {
            //string tmp1 = "�ɹ��������ӵ�"+std::to_string(i)+"��";
            //put_localmac(tmp1);
            printf("�ɹ��������ӵ�%d��\n", i);
        }

	    memset(recvBuffer, 0, 256);

	    int err = zmq_send(z_socket,msg, strlen(msg) ,0);//����ģʽ�����ĸ�����ΪZMQ_DONTWAIT��������ģʽ�ɹ������ֽ���
        if(err == strlen(msg))
        {
            //string tmp2 = "�ѷ��͵�"+std::to_string(i)+"��";
            //put_localmac(tmp2);
            printf("�ѷ��͵�%d��\n", i);
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
        
	    int recv = zmq_recv(z_socket, recvBuffer, 3, 0);//����ģʽ�����ĸ�����ΪZMQ_DONTWAIT��������ģʽ�ɹ�����0
        printf("%d",recv);
        if(recv == 3)
        {
            printf("�յ�Server�˻ش��%d��:%s\t\n",i,recvBuffer);
     
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
    int close = zmq_close(z_socket);//�ɹ�����0
    printf("close :%d\n",close);
    int destroy = zmq_ctx_destroy(context);//�ɹ�����0
    printf("destroy :%d\n",destroy);

}
int  main()
{
    //temp();//��֤�������
    demotrue();//��ȷdemo
    //SendMsgToAddin();//ԭdemo
}