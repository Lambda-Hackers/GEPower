#ifndef _COMMON_EVENT_H_
#define _COMMON_EVENT_H_
#include<windows.h>
#include<string>
#include<vector>
#include<algorithm>
#define _MAX_EVENT_NUM_ 1024

typedef void(*CALLBAK)(void*);

// use IOCP do event loop
namespace WINEVENT
{
    bool createEvent();

    void eventLoop(DWORD waitTime);

    bool addEvent(CALLBAK callbak, void* argt);
};

using namespace WINEVENT;
#endif