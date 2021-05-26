#include <iostream>
#include "luamgr.h"
#include "wedge.h"
using namespace std;

static LuaMgr* luaMgr;

bool init()
{
    // initialization log
    logOut::openStream("../log/run.log");
    return true;
}

int main()
{
    init();

    luaMgr = new LuaMgr();
    while(true)
    {
        Sleep(10*1000);
    }
    return 0;
}