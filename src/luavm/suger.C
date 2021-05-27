#include "suger.h"

/*--------------------------------------------------------------
* interface to Lua, Key word is create，use to create a new script
* object, have one table parameter, which describe the script.
* this func analyse the table and try to load the lua/C++ mode  
*/
int l_create(lua_State* L)
{
    if (lua_type(L, -1) != LUA_TTABLE) {
        log << "create() argv should be table, but get " << lua_type(L, -1) << endl;
        return 0;
    }

    // 
    return 0;
}

/*--------------------------------------------------------------
* interface to Lua, 
*/
int l_bind(lua_State *L)
{
    if (lua_type(L, -1) != LUA_TSTRING || lua_type(L, -2) != LUA_TFUNCTION) {
        log << "bind() argv should be (string, function), but get (" << lua_type(L, -1) << ", " 
            << lua_type(L, -2) << ")." << endl;
            return 0; 
    }
    
}


/*--------------------------------------------------------------
* register the key words to Lua 
*/
void U_Lua_loadCommonApi(lua_State *L)
{
    lua_register(L, "create", l_create);
    lua_register(L, "bind", l_bind);
    return;
}