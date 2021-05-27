#ifndef _COMMON_EVENT_H_
#define _COMMON_EVENT_H_
#include<windows.h>
#include<string>
#include<vector>
#include<algorithm>
#define _MAX_EVENT_NUM_ 1024

typedef void(*CALLBAK)(void*);

enum REGIST_EVENT {
    // model crash, send to the model which crash (A and B)
    CRASH,
    // model into the view
    INVIEW,
    // model move
    MOVE
};

// use IOCP do event loop
namespace WINEVENT
{
    bool createEvent();

    void eventLoop(DWORD waitTime);

    bool addEvent(CALLBAK callbak, void* argt);
};

using namespace WINEVENT;
#endif