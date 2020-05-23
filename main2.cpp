//#include <iostream>
//#include <boost/asio.hpp>
//#include <boost/bind.hpp>

//using namespace std;
//using boost::asio::ip::tcp;

//#define MAIL_SERVER "pop3.m.com" // 邮件服务器域名

//// pop3命令
//#define CMD_USER  "user myuser\n"
//#define CMD_PASS  "pass mypass\n"
//#define CMD_QUIT  "quitasdasaaaaa\n"

//// 接收缓存
//#define RECV_BUFFER_SIZE 1024

//// 异步socket事件处理类
//class async_socket_handler
//{
//private:
//    tcp::socket &m_sock;  // boost tcp socket
//    string m_status;      // 执行状态
//    char   m_buffer_1[RECV_BUFFER_SIZE];  // 消息接收缓存

//public:
//    async_socket_handler(tcp::socket &sock) : m_sock(sock), m_status("closed")
//    {
//        return;
//    }

//    // 当连接完成后，执行该方法
//    void on_connected(const boost::system::error_code& error)
//    {
//        if ( error == 0 ) {
//            // 连接成功，打印消息，
//            cout<<"info: connection has been established"<<endl;
//            m_status = "connected";

//            // 接收服务器欢迎消息，消息收到后，触发on_message_arrival消息执行
//            m_sock.async_read_some(boost::asio::buffer(m_buffer_1, RECV_BUFFER_SIZE),
//                                   boost::bind(&async_socket_handler::on_message_arrival,
//                                               this,
//                                               boost::asio::placeholders::error,
//                                               boost::asio::placeholders::bytes_transferred));
//        } else {
//            cout<<"error: failed to connect remote: "<<error<<endl;
//        }
//    } // end of on_connected

//    // 命令消息发送异步事件处理方法，当命令发送完成后，将执行该方法。
//    void on_message_sent(const boost::system::error_code& error, size_t size)
//    {
//        if ( error == 0 ) {
//            cout<<"info: "<<m_status<<",  "<<size<<" bytes sent"<<endl;

//            // 命令消息发送成功后，立即准备收消息，消息收到后，触发on_message_arrival消息执行
////            m_sock.async_read_some(boost::asio::buffer(m_buffer_1, RECV_BUFFER_SIZE),
////                                   boost::bind(&async_socket_handler::on_message_arrival,
////                                   this,
////                                   boost::asio::placeholders::error,
////                                   boost::asio::placeholders::bytes_transferred));
//        } else {
//            cout<<"error: "<<m_status<<" failed: "<<error<<endl;
//        }
//    }

//    // 收到远程返回的消息后, 此事件方法将被调用。
//    void on_message_arrival(const boost::system::error_code& error, size_t size)
//    {
//        if ( error ) {
//            cout<<"error: receive message failed, "<<error<<endl;
//            return ;
//        }

//        // 命令消息发送成功后，立即准备收消息，消息收到后，触发on_message_arrival消息执行
//        m_sock.async_read_some(boost::asio::buffer(m_buffer_1, RECV_BUFFER_SIZE),
//                               boost::bind(&async_socket_handler::on_message_arrival,
//                               this,
//                               boost::asio::placeholders::error,
//                               boost::asio::placeholders::bytes_transferred));
//        // 参数size表示收到的字节数，收到的消息位于m_buffer_1
//        m_buffer_1[size] = '\0';
//        cout<<m_buffer_1<<endl;
//        //cout<<m_status<<endl;

////        // 收消息成功，根据不同的状态分别处理
////        if ( m_status == string("connected")) {

////            // 连接后，收到服务器欢迎消息，发送用户登录命令
////            m_status = string("username_sent");
////            cout<<"begin send user name"<<endl;
////            m_sock.async_write_some(boost::asio::buffer(CMD_USER, strlen(CMD_USER)),
////                                    boost::bind(&async_socket_handler::on_message_sent,
////                                    this,
////                                    boost::asio::placeholders::error,
////                                    boost::asio::placeholders::bytes_transferred));
////        } else if (m_status == string("username_sent")) {

////            // 收到服务器用户名确认消息，接着发送口令命令
////            m_status = "password_sent";
////            cout<<"begin send password"<<endl;
////            m_sock.async_write_some(boost::asio::buffer(CMD_PASS, strlen(CMD_PASS)),
////                                    boost::bind(&async_socket_handler::on_message_sent,
////                                    this,
////                                    boost::asio::placeholders::error,
////                                    boost::asio::placeholders::bytes_transferred));
////        } else if (m_status == string("password_sent")) {

////            // 发送quit命令
////            m_status = "quit_sent";
////            cout<<"begin send quit"<<endl;
////            m_sock.async_write_some(boost::asio::buffer(CMD_PASS, strlen(CMD_QUIT)),
////                                    boost::bind(&async_socket_handler::on_message_sent,
////                                    this,
////                                    boost::asio::placeholders::error,
////                                    boost::asio::placeholders::bytes_transferred));
////        }else{
////            // 发送quit命令
////            m_status = "quit_sent";
////            cout<<"begin send quit"<<endl;
////            m_sock.async_write_some(boost::asio::buffer(CMD_PASS, strlen(CMD_QUIT)),
////                                    boost::bind(&async_socket_handler::on_message_sent,
////                                    this,
////                                    boost::asio::placeholders::error,
////                                    boost::asio::placeholders::bytes_transferred));
////        }
//        return ;
//    }
//};


//int main()
//{
//    boost::asio::io_service     ioservice;
//    tcp::socket    socket(ioservice);
////    tcp::endpoint  endpoint;
////    boost::system::error_code errcode;
////    tcp::resolver resolver(ioservice);
////    tcp::resolver::iterator iter_endpoint, iter_null;
////    tcp::resolver::query query(MAIL_SERVER, "pop3");
//    async_socket_handler handler(socket);  // 处理socket异步事件回调

//    // 域名解析
////    iter_endpoint = resolver.resolve(query, errcode);
////    endpoint = iter_endpoint->endpoint();

//    //boost::asio::io_service m_io;
//    tcp::endpoint * m_pEndPoint;
//    tcp::socket * m_pSocket;

//    m_pEndPoint = new tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 6002);
//    m_pSocket = new tcp::socket(ioservice);
//    m_pSocket->open(m_pEndPoint->protocol());
//    try {
//        // 首先执行异步连接，此后的操作在async_socket_handler中
//        // 根据不同的命令状态一次完成。
//        socket.async_connect(*m_pEndPoint,
//                             boost::bind(&async_socket_handler::on_connected,
//                                         &handler,
//                                         boost::asio::placeholders::error));

//        ioservice.run();  // 启动异步io过程
//        cout<<"io service running finished"<<endl;
//        socket.close();  // 通讯过程完成后，关闭socket
//    } catch (const boost::system::system_error& e) {
//        cout<<"connect error: "<<e.what()<<endl;
//    }
//    return 0;
//} // end of main
