#include <iostream>
#include "wedge.h"
#include "luamgr.h"
using namespace std;

static LuaMgr* luaMgr;

int main()
{
    cout << 111 << endl;
    luaMgr = new LuaMgr();
    while(true)
    {
        Sleep(10*1000);
        cout << 111 << endl;
    }
    return 0;
}