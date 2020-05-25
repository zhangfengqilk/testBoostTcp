#pragma once

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
#include <boost/typeof/typeof.hpp>

#include <boost/signals2.hpp>
#include <boost/function.hpp>
#include <iostream>
#include <vector>
#include <string>
using namespace boost::asio;
using namespace std;
using namespace boost;
#define			TCP_RECV_DATA_PACKAGE_MAX_LENGTH				1024
#define CALLBACK
typedef  unsigned int       DWORD;
typedef  unsigned short     WORD;
typedef  unsigned short     USHORT;
typedef  short              SHORT;
typedef  int                LONG;
typedef  unsigned char      BYTE;
typedef  unsigned int       UINT;
typedef  void*              LPVOID;
typedef  void*              HANDLE;
typedef  unsigned int*      LPDWORD;
typedef  unsigned long long UINT64;
typedef  signed long long   INT64;
//接收数据类型
typedef enum RecvDataType
{
    RecvDataType_NoKnown		=		0x00,			//未知
    RecvDataType_Head			=		0x01,			//头数据
    RecvDataType_Body			=		0x02,			//体数据
    RecvDataType_Some			=		0x03,			//部分数据
    RecvDataType_OnePackage		=		0x04,			//整包数据
}RecvDataType;

//发送数据回调函数
typedef void (CALLBACK *TcpSendDataCallback)(const boost::system::error_code& error,std::size_t bytes_transferred,DWORD dwUserData1,DWORD dwUserData2);

//接收数据回调函数
typedef void (CALLBACK *TcpRecvDataCallback)(const boost::system::error_code& error,char *pData,int nDataSize,DWORD dwUserData1,DWORD dwUserData2);

class TcpClient
{
public:
    TcpClient(void);
    virtual ~TcpClient(void);

    //设置参数
    void	SetParameter(unsigned int uiSendBufferSize,unsigned int uiSendTimeout,unsigned int uiRecvBufferSize,unsigned int uiRecvTimeout);

    //设置阻塞与非阻塞
    void	SetNoBlock(bool bNoBlock);

    //连接服务器(同步)
    int		ConnectServer(char *pIp,unsigned short usPort,unsigned int uiConnectTimeout);

    //连接服务器(异步)
    int		ConnectServerByAynsc(char *pIp,unsigned short usPort,unsigned int uiConnectTimeout,unsigned int uiReconnectInteralTime);

    //关闭连接
    void	CloseConnect();

    //发送数据
    int		SendData(char *pBuffer,int nBufferSize);

    //接收数据
    int		RecvData(char *pBuffer,int nBufferSize);

    //接收数据(阻塞)
    int		RecvDataByBlock(char *pBuffer,int nBufferSize);

    //发送数据(异步)
    int		SendDataByAynsc(char *pBuffer,int nBufferSize,TcpSendDataCallback fnCallback,DWORD dwUserData1,DWORD dwUserData2);

    //接收数据(异步)
    int		RecvDataByAynsc(TcpRecvDataCallback fnCallback,DWORD dwUserData1,DWORD dwUserData2);
    void RunAynsc();


public:
    //typedef 信号
    typedef boost::signals2::signal<void(const boost::system::error_code&,char*,int)> defSignal;
    typedef typename defSignal::slot_type defSlot;
    //连接槽函数
    boost::signals2::connection connectFun(const defSlot& slot){
         return mSignal.connect(slot);
    }
    void test(){
        //mSignal(10,20);
    }
private:
        defSignal mSignal;
protected:
    void connect_handler(const boost::system::error_code& ec);
    void async_read_handler(const boost::system::error_code& ec,size_t bytes_transferred,TcpRecvDataCallback fnCallback,DWORD dwUserData1,DWORD dwUserData2);
    void read_hander(char *pBuffer,size_t bytes_transferred,const boost::system::error_code& err);
    void write_handler(const boost::system::error_code& error,size_t bytes_transferred,TcpSendDataCallback fnCallback,DWORD dwUserData1,DWORD dwUserData2);

    void RecvDataTimeoutProcess();
    void on_message_arrival(const boost::system::error_code& error, size_t size);

    io_service m_io;
    ip::tcp::endpoint * m_pEndPoint;
    ip::tcp::socket * m_pSocket;
    boost::array<char,TCP_RECV_DATA_PACKAGE_MAX_LENGTH> m_rbTempRecvBuffer;		//临时接收数据缓冲区

    int m_nSyncRecviceDataSize;				//同步接收数据大小

    unsigned int m_uiSendBufferSize;
    unsigned int m_uiSendTimeout;
    unsigned int m_uiRecvBufferSize;
    unsigned int m_uiRecvTimeout;

    deadline_timer * m_pTimer;
    char   m_buffer_1[TCP_RECV_DATA_PACKAGE_MAX_LENGTH];  // 消息接收缓存
};
