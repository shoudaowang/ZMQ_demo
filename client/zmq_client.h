#include "zmq.h"
#include "zmq_utils.h"
#include <windows.h>
#include <stdarg.h>
#include <atltrace.h>
#include <string>
#include <fstream> 
#include <iostream> 
using namespace std;
void SendMsgToAddin(const char* msg,int i);
/*
void put_localmac(const string local_mac)
{
    ofstream outfile("client.txt", ios::app); 
    outfile << local_mac; 
    outfile << endl;
    outfile.close();
    
}
*/