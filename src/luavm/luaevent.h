#ifndef _LUAVM_LUAEVENT_H_
#define _LUAVM_LUAEVENT_H_
#include<map>
#include"../common/event.h"

enum REGIST_EVENT {
    // model crash, send to the model which crash (A and B)
    CRASH,
    // model into the view
    INVIEW,
    // model move
    MOVE
};

class LuaEvent
{
public:
    LuaEvent();
    ~LuaEvent();

private:
    // std::map<REG>
};




#endif
