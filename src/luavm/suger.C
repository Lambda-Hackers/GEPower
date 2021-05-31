#include"suger.h"
#include"script.h"
#include"../include/lua/dump.h" 
#include<vector>
#include<algorithm>

/*--------------------------------------------------------------
* interface to Lua, bind(msg name, deal func[, argv])
*/
int l_bind(lua_State *L)
{
    // not argv table, push {} to stack
    if (lua_gettop(L) != 3)
        lua_newtable(L);

    if (lua_type(L, 1) != LUA_TSTRING || lua_type(L, 2) != LUA_TFUNCTION || lua_type(L, 3) != LUA_TTABLE) {
        log << "bind() argv should be (string, function[, table]), but get (" << lua_type(L, 1) << ", " 
            << lua_type(L, 2) << ", " << lua_type(L, 3) << ")." << endl;
            return 0; 
    }

    Script* script = (Script*)lua_touserdata(L, lua_upvalueindex(1));
    if (script == NULL)
    {
        log << "script had been destory, exit" << endl;
        return 0;
    }

    // analysis argv table
    int _index = 0;
    while (lua_geti(L, 3, ++_index) == LUA_TSTRING)
    {
        string str = lua_tostring(L, -1);
        if (str == "ordinate")
        {

        } else if (str == "mutual")
        {

        } else if (str == "time")
        {
            
        }
    }

    // analysis msg event name
    string event = lua_tostring(L, -3);
    if (event == "CRASH")
    {
        script->crash();
    }
    return 0;
}

const luaL_Reg funcRegist[] = {
    {"bind", l_bind},
    {NULL, NULL}
};

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

    Script* script = new Script(L);

    // traversal argv table get property of script
    lua_pushnil(L);
    while(lua_next(L, -2))
    {
        if (lua_type(L, -2) != LUA_TSTRING) {
            lua_pop(L, 1);
            continue;
        }
        string str = lua_tostring(L, -2);
        if (str == "NAME" || str == "name")
        {
            script->setScriptName(lua_tostring(L, -1));
        }
        lua_pop(L, 1);
    }

	lua_createtable(L, 0, 8);
	for (const luaL_Reg *l = funcRegist; l->name != NULL; l++) {
		lua_pushstring(L, l->name);
		lua_pushlightuserdata(L, (void *)script);
		lua_pushcclosure(L, l->func, 1);
		lua_settable(L, -3);
	}
    log << "lua create script OK" <<endl;
    return 1;
}

/*--------------------------------------------------------------
* register the key words to Lua 
*/
void U_Lua_loadCommonApi(lua_State *L)
{
    lua_register(L, "create", l_create);
    luaL_newlibtable(L, funcRegist);

    lua_setglobal(L, "_funcRegist");

    log << "load common Api OK !" << endl;
    return;
}