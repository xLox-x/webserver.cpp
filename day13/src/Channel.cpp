/******************************
*   author: yuesong-feng
*   
*
*
******************************/
#include "Channel.h"
#include "EventLoop.h"
#include "Socket.h"
#include <unistd.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <iostream>
Channel::Channel(EventLoop *_loop, int _fd) 
    : loop(_loop), fd(_fd), events(0), ready(0), inEpoll(false){}

Channel::~Channel(){
    std::cout << "Channel dctor" << std::endl;
    if(fd != -1){
        loop->deleteChannel(this);
        close(fd);
        fd = -1;
    }
}

void Channel::handleEvent(){
    if(ready & (EPOLLIN | EPOLLPRI)){
        readCallback();
    }
    if(ready & (EPOLLOUT)){
        writeCallback();
    }

}

void Channel::enableRead(){
    events |= EPOLLIN | EPOLLPRI;
    loop->updateChannel(this);
}

void Channel::useET(){
    events |= EPOLLET;
    loop->updateChannel(this);
}
int Channel::getFd(){
    return fd;
}

uint32_t Channel::getEvents(){
    return events;
}
uint32_t Channel::getReady(){
    return ready;
}

bool Channel::getInEpoll(){
    return inEpoll;
}

void Channel::setInEpoll(bool _in){
    inEpoll = _in;
}

void Channel::setReady(uint32_t _ev){
    ready = _ev;
}

void Channel::setReadCallback(std::function<void()> _cb){
    readCallback = _cb;
}
