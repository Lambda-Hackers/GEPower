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
        *logOut::getStream() << "xxxxxxxxxx" << endl;
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
    luaL_dofile(m_L, m_scriptPath.c_str());

    CreateThread(NULL, 0, threadRun, this, 0, NULL);
    return true;
}

