/******************************
*   author: yuesong-feng
*   
*
*
******************************/
#include "EventLoop.h"
#include "Epoll.h"
#include "Channel.h"
#include <vector>
#include <iostream>

EventLoop::EventLoop() : ep(nullptr), quit(false){
    ep = new Epoll();
}

EventLoop::~EventLoop(){
    std::cout << "EventLoop dctor" << std::endl;
    delete ep;
}


void EventLoop::loop(){
    while(!quit){
    std::vector<Channel*> chs;
        chs = ep->poll();
        for(auto it = chs.begin(); it != chs.end(); ++it){
            (*it)->handleEvent();
        }
    }
}

void EventLoop::updateChannel(Channel *ch){
    ep->updateChannel(ch);
}


void EventLoop::deleteChannel(Channel *channel){
    ep->deleteChannel(channel);
}
