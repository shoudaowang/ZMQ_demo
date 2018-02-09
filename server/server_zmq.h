#include "zmq.h"
//#include "zmq_utils.h"
//#include "string_utils.h"
//#include "utils.h"
#include <string>
#include <fstream> 
#include <iostream> 
using namespace std;

void put_localmac(const string local_mac)
{
    ofstream outfile("client.txt", ios::app); 
    outfile << local_mac; 
    outfile << endl;
    outfile.close();
    
}