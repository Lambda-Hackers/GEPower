#ifndef _LUA_COMMON_HEADER_
#define _LUA_COMMON_HEADER_

#include "lua.h"
#include "../../common/logout.h"

static size_t BUFF_LENGTH;

static const char* getStrLuaType(int type)
{
    switch (type)
    {
    case LUA_TNIL:
        return "LUA_TNIL";
    case LUA_TBOOLEAN:
        return "LUA_TBOOLEAN";
    case LUA_TLIGHTUSERDATA:
        return "LUA_TLIGHTUSERDATA";
    case LUA_TNUMBER:
        return "LUA_TNUMBER";
    case LUA_TSTRING:
        return "LUA_TSTRING";
    case LUA_TTABLE:
        return "LUA_TTABLE";
    case LUA_TFUNCTION:
        return "LUA_TFUNCTION";
    case LUA_TUSERDATA:
        return "LUA_TUSERDATA";
    case LUA_TTHREAD:
        return "LUA_TTHREAD";
    default:
        break;
    }
    return "LUA_UNKONWTYPE";
}

static const char* getStrLuaState(lua_State* L)
{
    switch (lua_status(L))
    {
    case LUA_OK:
        return "LUA_OK";
    case LUA_YIELD:
        return "LUA_YIELD";
    case LUA_ERRRUN:
        return "LUA_ERRRUN";
    case LUA_ERRSYNTAX:
        return "LUA_ERRSYNTAX";
    case LUA_ERRMEM:
        return "LUA_ERRMEM";
    case LUA_ERRERR:
        return "LUA_ERRERR";
    default:
        break;
    }
    return "LUA_UNKONWSTATE";
}

static void dumptable(lua_State *L, int depth = 0)
{
    debug("(%p)", (void *)lua_topointer(L, -1));
    if (lua_gettop(L) < 1 || lua_type(L, -1) != LUA_TTABLE) {
        debug("not table on the top of stack");
        return;
    }

    lua_pushnil(L);
    while (lua_next(L, -2))
    {
        char buff[BUFF_LENGTH];
        int pos_buff = 0;
        for (int i = 0; i < depth; ++i)
            buff[pos_buff++] = '\t';

        switch (lua_type(L, -2))
        {
        case LUA_TNUMBER:
            pos_buff += snprintf(buff+pos_buff, BUFF_LENGTH-pos_buff, "TK=%ld\t", lua_tointeger(L, -2));
            break;
        case LUA_TSTRING:
            pos_buff += snprintf(buff+pos_buff, BUFF_LENGTH-pos_buff, "TK=%s\t", lua_tostring(L, -2));
            break;
        case LUA_TUSERDATA:
            pos_buff += snprintf(buff+pos_buff, BUFF_LENGTH-pos_buff, "TK=%p\t", lua_touserdata(L, -2));
            break;
        default:
            break;
        }

        int type = lua_type(L, -1);
        switch (type)
        {
        case LUA_TTABLE:
            dumptable(L, depth+1);
            break;
        case LUA_TNUMBER:
            pos_buff += snprintf(buff+pos_buff, BUFF_LENGTH-pos_buff, "TV=%ld", lua_tointeger(L, -2));
            break;
        case LUA_TSTRING:
            pos_buff += snprintf(buff+pos_buff, BUFF_LENGTH-pos_buff, "TV=%s", lua_tostring(L, -2));
            break;
        case LUA_TUSERDATA:
            pos_buff += snprintf(buff+pos_buff, BUFF_LENGTH-pos_buff, "TV=%p", lua_touserdata(L, -2));
            break;
        default:
            break;
        }
        debug(buff);

        lua_pop(L, 1);
    }
}

static void dumpstack(lua_State *L, const char* str, bool print_all = false)
{
    int num = 0;
    if (print_all)
        num = -lua_gettop(L);
    else
        num = L->top - (L->stack + 1);

    char buff[BUFF_LENGTH];
    int pos_buff = 0;
    int cacheTop = lua_gettop(L);
    debug("<------------dump begin------------>");
    debug("<%s> lua_State(%p) %s, elements: %d\n", str, L, getStrLuaState(L), lua_gettop(L));
    for (int i = -1; i >= num; --i)
    {
		int type = lua_type(L, i);
		pos_buff += snprintf(buff+pos_buff, BUFF_LENGTH-pos_buff, "R%02d T=%s\t ", num+1+i, lua_typename(L, type));
		switch (type)
		{
		case LUA_TNUMBER:
			pos_buff += snprintf(buff+BUFF_LENGTH, BUFF_LENGTH-pos_buff, "V=%ld", lua_tointeger(L, i));
			break;
		case LUA_TSTRING:
			pos_buff += snprintf(buff+BUFF_LENGTH, BUFF_LENGTH-pos_buff, "V=\"%s\"", lua_tostring(L, i));
			break;
		case LUA_TTABLE:
			lua_pushvalue(L, i);
			dumptable(L, 1);
			lua_settop(L, cacheTop);
			break;
		case LUA_TFUNCTION:
			if (lua_iscfunction(L, i)) pos_buff += snprintf(buff+BUFF_LENGTH, BUFF_LENGTH-pos_buff, "(C)");
			else pos_buff += snprintf(buff+BUFF_LENGTH, BUFF_LENGTH-pos_buff, "(Lua)");
			pos_buff += snprintf(buff+BUFF_LENGTH, BUFF_LENGTH-pos_buff, "V=%p", (void *)lua_topointer(L, i));
			break;
		case LUA_TTHREAD:
			pos_buff += snprintf(buff+BUFF_LENGTH, BUFF_LENGTH-pos_buff, "V=%p", (void *)lua_tothread(L, i));
			break;
		case LUA_TBOOLEAN:
			pos_buff += snprintf(buff+BUFF_LENGTH, BUFF_LENGTH-pos_buff, "V=%s", lua_toboolean(L, i) ? "true" : "false");
			break;
		case LUA_TUSERDATA:
		case LUA_TLIGHTUSERDATA:
			pos_buff += snprintf(buff+BUFF_LENGTH, BUFF_LENGTH-pos_buff, "V=%p", (void *)lua_touserdata(L, i));
			break;
		case LUA_TNIL:
			pos_buff += snprintf(buff+BUFF_LENGTH, BUFF_LENGTH-pos_buff, "V=(nil)");
			break;
		default:
			pos_buff += snprintf(buff+BUFF_LENGTH, BUFF_LENGTH-pos_buff, "V=(oops)");
			break;
        }
    }
    debug(buff);
    debug("<-------------dump end------------->");
}

#endif