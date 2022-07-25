#include "LuaMgr.h"

using namespace std;

/*--------------------------------------------------------------
* init LuaMgr
*/
LuaMgr::LuaMgr()
{
    // Load main Lua scrite
    m_luaState = luaL_newstate();

    // opens all standard Lua libraries into the given state
    luaL_openlibs(m_luaState);

    if (luaL_dofile(m_luaState, "../script/main.Lua") != LUA_OK)
    {
        warn("err to exec lua scripte path: %s", MAIN_LUA_PATH);
        exit(1);
    }
}

LuaMgr::~LuaMgr()
{
}


