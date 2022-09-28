#include "LuaMgr.h"

using namespace std;

static int l_include(lua_State* L)
{
	if (!lua_isstring(L, 1)) {
		warn("should include _string_, ignore it");
		return luaL_error(L, "include %s", lua_typename(L, lua_type(L, 1)));
	}

    LuaMgr* luaMgr = getMgr(L);
    const char* libname = lua_tostring(L, 1);

    if (!luaMgr->getLibMgr()->l_include(libname))
    {
        return luaL_error(L, "include %s error!", libname);
    }

    return 0;
}

/*--------------------------------------------------------------
* init LuaMgr
*/
LuaMgr::LuaMgr()
{
    // Load main Lua scrite
    m_luaState = luaL_newstate();

    // push LuaMgr point to the bottom of stack
    lua_pushlightuserdata(m_luaState, this);

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
    // 关闭 Lua_State
    lua_close(m_luaState);
}


