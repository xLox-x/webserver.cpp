#include "TcpConnection.h"
#include "Buffer.h"
#include "Channel.h"
#include "common.h"
#include "EventLoop.h"

#include <memory>
#include <unistd.h>
#include <assert.h>
#include <iostream>
#include <sys/socket.h>



TcpConnection::TcpConnection(EventLoop *loop, int connfd, int connid): connfd_(connfd), connid_(connid), loop_(loop){

    if (loop != nullptr)
    {
        channel_ = std::make_unique<Channel>(connfd, loop);
        channel_->EnableET();
        channel_->set_read_callback(std::bind(&TcpConnection::HandleMessage, this));
        channel_->EnableRead();
    }
    read_buf_ = std::make_unique<Buffer>();
    send_buf_ = std::make_unique<Buffer>();
}

TcpConnection::~TcpConnection(){
    std::cout << " TcpConnection::dctor" << std::endl;
    ::close(connfd_);
}

void TcpConnection::set_close_callback(std::function<void(int)> const &fn) { 
    on_close_ = std::move(fn); 
}
void TcpConnection::set_message_callback(std::function<void(TcpConnection *)> const &fn) { 
    on_message_ = std::move(fn);
}

void TcpConnection::HandleMessage(){
    Read();
    if (on_message_ && !isDisconnected())
    {
        std::cout << "TcpConnection HandleMessage before" << std::endl;
        on_message_(this);
        std::cout << "TcpConnection HandleMessage end" << std::endl;
    }
}

void TcpConnection::HandleClose() {
    std::cout << " TcpConnection::HandleClose" << std::endl;
    if (state_ != ConnectionState::Disconected)
    {
        state_ = ConnectionState::Disconected;
        if(on_close_){
            on_close_(connfd_);
        }
    }
}

bool TcpConnection::isDisconnected() {
    return state_ == ConnectionState::Disconected;
}



EventLoop *TcpConnection::loop() const { return loop_; }
int TcpConnection::id() const { return connid_; }
int TcpConnection::fd() const { return connfd_; }
TcpConnection::ConnectionState TcpConnection::state() const { return state_; }
void TcpConnection::set_send_buf(const char *str) { send_buf_->set_buf(str); }
Buffer *TcpConnection::read_buf(){ return read_buf_.get(); }
Buffer *TcpConnection::send_buf() { return send_buf_.get(); }

void TcpConnection::Send(const std::string &msg){
    set_send_buf(msg.c_str());
    Write();
}

void TcpConnection::Send(const char *msg){
    set_send_buf(msg);
    Write();
}

void TcpConnection::Read()
{
    read_buf_->Clear();
    ReadNonBlocking();
    std::cout << "TcpConnection after read" << std::endl;
}

void TcpConnection::Write(){
    WriteNonBlocking();
    send_buf_->Clear();
}


void TcpConnection::ReadNonBlocking(){
    char buf[1024];
    while(true){
        memset(buf, 0, sizeof(buf));
        ssize_t bytes_read = read(connfd_, buf, sizeof(buf));
        if(bytes_read > 0){
            read_buf_->Append(buf, bytes_read);
        }else if(bytes_read == -1 && errno == EINTR){
            std::cout << "ReadNonBlocking continue reading" << std::endl;
            continue;
        }else if((bytes_read == -1) && (
            (errno == EAGAIN) || (errno == EWOULDBLOCK))){
            break;
        }else if (bytes_read == 0){//
            std::cout << "ReadNonBlocking 0 byte close" << std::endl;
            HandleClose();
            break;
        }else{
            std::cout << "ReadNonBlocking unknow close" << std::endl;
            HandleClose();
            break;
        }
    }
}

void TcpConnection::WriteNonBlocking(){
    char buf[send_buf_->Size()];
    memcpy(buf, send_buf_->c_str(), send_buf_->Size());
    int data_size = send_buf_->Size();
    int data_left = data_size;

    while(data_left > 0){
        ssize_t bytes_write = write(connfd_, buf + data_size - data_left, data_left);
        if(bytes_write == -1 && errno == EINTR){
            std::cout << "continue writing" << std::endl;
            continue;
        }
        if(bytes_write == -1 && errno == EAGAIN){
            break;
        }
        if(bytes_write == -1){
            std::cout << "WriteNonBlocking -1 byte" << std::endl;
            HandleClose();
            break;
        }
        data_left -= bytes_write;
    }
}
