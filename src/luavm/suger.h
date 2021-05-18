#ifndef LUA_SUGER
#define LUA_SUGER
#include "wedge.h"

// try to load user_defined api
void U_Lua_loadCommonApi(lua_State* L);

// create
int l_create(lua_State* L);
#endif