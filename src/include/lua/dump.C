
#include"dump.h"
#include"../../common/logout.h"

void dumpstack(lua_State *L, const string& str)
{
    int num = lua_gettop(L);
    log << "<dumpstack>" << str << ": num = " << num << endl;
    for (int i = -1; i >= -num; --i)
    {
        int index = i;
        log << "[" << index << "]";
        switch (lua_type(L, index))
        {
        case LUA_TNUMBER:
            log << " LUA_TNUMBER       : " <<  lua_tonumber(L, index) << endl;
            break;
        case LUA_TSTRING:
            log << " LUA_TSTRING       : " <<  lua_tostring(L, index) << endl;
            break;
        case LUA_TFUNCTION:
            log << " LUA_TFUNCTION     : " <<  lua_topointer(L, index) << endl;
            break;
        case LUA_TLIGHTUSERDATA:
            log << " LUA_TLIGHTUSERDATA: " << lua_touserdata(L, index) << endl;
            break;
        case LUA_TNIL:
            log << " LUA_TNIL          : nil" << endl;
            break;
        case LUA_TTABLE:
            log << " LUA_TTABLE        : table" << endl;
            break; 
        default:
            break;
        }
    }
}