// "Copyright [2017] <Copyright SebastianBlanco>"
#ifndef  _HOME_SEBASTIAN_CLIONPROJECTS_TP3_COMMONTHREADS_H_
#define  _HOME_SEBASTIAN_CLIONPROJECTS_TP3_COMMONTHREADS_H_
//--------------------------------------------------------------------------
#include <thread>
//--------------------------------------------------------------------------
class Thread {
 protected :
    std::thread thread;
 public :
    Thread();
    //--------------------------------------------------------------------------
    void start();
    //--------------------------------------------------------------------------
    void join();
    //--------------------------------------------------------------------------
    virtual void run() = 0;
    //--------------------------------------------------------------------------
    virtual ~Thread();
    //--------------------------------------------------------------------------
    Thread(const Thread&) = delete;
    //--------------------------------------------------------------------------
    Thread& operator=(const Thread&) = delete;
    //--------------------------------------------------------------------------
    Thread(Thread&& other);
    //--------------------------------------------------------------------------
    Thread& operator=(Thread&& other);
    //--------------------------------------------------------------------------
};

#endif  // _HOME_SEBASTIAN_CLIONPROJECTS_TP3_COMMONTHREADS_H_