#include <iostream>
#include "wedge.h"
#include "luamgr.h"
using namespace std;

static LuaMgr* luaMgr;

int main()
{
    luaMgr = new LuaMgr();
    while(true)
    {
        Sleep(10*1000);
    }
    return 0;
}