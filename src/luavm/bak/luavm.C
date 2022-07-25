#include"luavm.h"
#include"suger.h"

/*--------------------------------------------------------------
* thread Loop for Lua Vm
*/
DWORD WINAPI threadRun(LPVOID argv)
{
    LuaVm* vm = (LuaVm*)argv;
    // call default lua func script_run, must be a globe func
    lua_getglobal(vm->L(), "script_run");
    log << lua_type(vm->L(), -1) << endl;
    switch (lua_pcall(vm->L(), 0, 0, 0))
    {
    case LUA_OK:
        break;
    case LUA_ERRRUN:
        log << "run script_run func err, end lua vm thread" << endl;
        return 0;
    case LUA_ERRMEM:
        log << "memory allocation err, end lua vm thread" << endl;
        return 0;
    case LUA_ERRERR:
        log << "some err in script_run, end lua vm thread" << endl;
        return 0;
    default:
        log << "Something unexpected when run script_run, end lua vm thread" << endl;
        return 0;
    }
    log << "exit" << endl;
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
    // set globle table G_EVENT_REFLECT
    lua_newtable(m_L);
    lua_setglobal(m_L, "G_EVENT_REFLECT");

    if (luaL_dofile(m_L, m_scriptPath.c_str()) != LUA_OK)
    {
        log << "err to exec lua scripte path: "<< m_scriptPath << endl;
        return false;
    }

    if (CreateThread(NULL, 0, threadRun, this, 0, NULL) == INVALID_HANDLE_VALUE)
    {
        return false;
    }
    return true;
}

