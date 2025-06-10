#pragma once
#include "common.h"
#include <functional>
#include <unordered_map>
#include <vector>
#include <memory>
class EventLoop;
class TcpConnection;
class Acceptor;
class ThreadPool;
class TcpServer
{
    public:
    DISALLOW_COPY_AND_MOVE(TcpServer);
    TcpServer(const char *ip, const int port);
    ~TcpServer();

    void Start();

    void set_connection_callback(std::function < void(TcpConnection *)> const &fn);
    void set_message_callback(std::function < void(TcpConnection *)> const &fn);

    void HandleClose(int fd);
    void HandleNewConnection(int fd);

    private:
        std::unique_ptr<EventLoop> main_reactor_;
        int next_conn_id_;
        
        std::unique_ptr<Acceptor> acceptor_;
        std::vector<std::unique_ptr<EventLoop>> sub_reactors_;
        //std::unordered_map<int, std::unique_ptr<TcpConnection>> connectionsMap_;
	std::unordered_map<int, TcpConnection *> connectionsMap_;
        
        std::unique_ptr<ThreadPool> thread_pool_;

        std::function<void(TcpConnection *)> on_connect_;
        std::function<void(TcpConnection *)> on_message_;

};
