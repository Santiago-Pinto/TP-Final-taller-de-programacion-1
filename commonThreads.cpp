// "Copyright [2017] <Copyright SebastianBlanco>"
#include <utility>
#include <iostream>
#include "commonThreads.h"
//------------------------------------------------------------------------------
// THREAD
//------------------------------------------------------------------------------
Thread::Thread() {}
//------------------------------------------------------------------------------
// ~THREAD
//------------------------------------------------------------------------------
Thread::~Thread() {
    if (thread.joinable()) {
        std::terminate();
    }
}
//------------------------------------------------------------------------------
// START
//------------------------------------------------------------------------------
void Thread::start() {
    thread = std::thread(&Thread::run, this);
}
//------------------------------------------------------------------------------
// JOIN
//------------------------------------------------------------------------------
void Thread::join() {
    thread.join();
}
//------------------------------------------------------------------------------
// RUN
//------------------------------------------------------------------------------
void Thread::run() {}
//------------------------------------------------------------------------------
// THREAD
//------------------------------------------------------------------------------
Thread::Thread(Thread&& other) {
    this->thread = std::move(other.thread);
}
//------------------------------------------------------------------------------
// OPERATOR =
//------------------------------------------------------------------------------
Thread& Thread::operator=(Thread&& other) {
    this->thread = std::move(other.thread);
    return *this;
}
//------------------------------------------------------------------------------