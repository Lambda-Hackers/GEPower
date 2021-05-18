#include "suger.h"

int l_create(lua_State* L)
{
    return 0;
}

void U_Lua_loadCommonApi(lua_State *L)
{
    lua_register(L, "create", l_create);
    return;
}