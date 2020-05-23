#include <iostream>
#include "TcpClient.h"
using namespace std;

void CALLBACK tcpRecvDataCallback(const boost::system::error_code& error,char *pData,int nDataSize,DWORD dwUserData1,DWORD dwUserData2){
    cout<<"recive data"<<endl;
}
int main()
{
    TcpClient tc;
    //tc.ConnectServer("127.0.0.1",6002,600);
    tc.ConnectServerByAynsc("127.0.0.1",6002,600,1000);
    //tc.RecvData()
    tc.RunAynsc();
    cout << "Hello World!" << endl;
    return 0;
}
