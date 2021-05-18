#include"luavm.h"
#include"suger.h"

/*--------------------------------------------------------------
* thread Loop for Lua Vm
*/
DWORD WINAPI threadRun(LPVOID vm)
{
    vm = (LuaVm *)vm;
    int i = 10;
    while (i--)
    {
        out("xxxx");
    }
    return 0;
}

LuaVm::LuaVm(string path)
{
    m_scriptPath = path;

    m_L = luaL_newstate();
    luaL_openlibs(m_L);
    U_Lua_loadCommonApi(m_L);
}

LuaVm::~LuaVm()
{
    lua_close(m_L);
}

/*--------------------------------------------------------------
* this func is use to initialization the vm
*/
bool LuaVm::initLuaVm()
{
    CreateThread(NULL, 0, threadRun, this, 0, NULL);
    return true;
}

