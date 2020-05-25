#include <iostream>
#include "TcpClient.h"
using namespace std;
TcpClient tc;
void startTcp();

//接收信号后响应的函数
class FunRecv1{

public:
    void action(const boost::system::error_code& error,char *pData,int nDataSize){
        cout<<"recive data"<<endl;
        cout<<pData<<endl;
        cout<<error<<endl;
        //tc.SendData("hello",5);

        if(error==boost::asio::error::eof){
            cout<<"server has disconnected"<<endl;
            sleep(1);
            startTcp();
        }else if(error==boost::asio::error::connection_refused){
            cout<<"server has refused"<<endl;
            sleep(1);
            startTcp();
        }
    }

};


void CALLBACK tcpRecvDataCallback(const boost::system::error_code& error,char *pData,int nDataSize,DWORD dwUserData1,DWORD dwUserData2){

    cout<<"recive data"<<endl;
    cout<<pData<<endl;
    cout<<error<<endl;
    //tc.SendData("hello",5);

    if(error==boost::asio::error::eof){
        cout<<"server has disconnected"<<endl;
        sleep(1);
        startTcp();
    }else if(error==boost::asio::error::connection_refused){
        cout<<"server has refused"<<endl;
        sleep(1);
        startTcp();
    }

}
void startTcp(){
    cout<<"connect to server"<<endl;
    int re=tc.ConnectServerByAynsc("103.149.26.221",8390,12600,4000);
    if(re<0){
        return ;
    }
    //tc.RecvDataByAynsc(tcpRecvDataCallback,0,1);
    //tc.RecvData()
    tc.RunAynsc();
}
int main()
{
    FunRecv1 fun1;
    char * a;
    boost::signals2::connection con1 = tc.connectFun(boost::bind(&FunRecv1::action,&fun1,_1,_2,_3));
    //tc.test();
    startTcp();
    //tc.ConnectServer("127.0.0.1",6002,600);

    cout << "Hello World!" << endl;
    return 0;
}
