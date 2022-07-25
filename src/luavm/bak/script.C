
#include"script.h"
#include"../include/lua/dump.h" 

static unsigned int g_scriptNUM;

static unsigned int genScriptHashCode()
{
    return ++g_scriptNUM;
}

Script::Script(lua_State* l)
{
    m_L = l;
    m_hashcode = genScriptHashCode();
}

Script::~Script()
{
}

// name(int) & func(int) should > 0
bool Script::setEvent(const int& name, const int& func)
{
    if (lua_getglobal(m_L, "G_EVENT_REFLECT") != LUA_TTABLE)
    {
        log << "bind event failed, globle table G_EVENT_REFLECT is not a table" << endl;
        return false;
    }

    lua_pushstring(m_L, m_hashcode.c_str());
    if (lua_gettable(m_L, -2) != LUA_TTABLE)
    {
        lua_pop(m_L, 1);
        lua_createtable(m_L, 0, 8);
    }
    lua_pushvalue(m_L, name);
    lua_pushvalue(m_L, func);
    lua_settable(m_L, -3);

    dumpstack(m_L, "xxx");
    return true;
}
// script deal msg crash fun
void Script::crash(void* p)
{
    if (p == NULL)
    {
        log << "script:crash() err, don't kown the another parties" << endl;
        return;
    }
}

// set script attribute to the table
void Script::setTableValue(Script* parties)
{
    lua_createtable(m_L, 0, 0);

    // push time onto the lua state
    lua_pushstring(m_L, "time");
    lua_pushstring(m_L, "20210531123000");
    lua_settable(m_L, -3);

    // push script name onto lua state
    lua_pushstring(m_L, "name");
    lua_pushstring(m_L, m_scrpteName.c_str());
    lua_settable(m_L, -3);

    // push the only hash ID onto lua state
    lua_pushstring(m_L, "hashcode");
    lua_pushstring(m_L, m_hashcode.c_str());
    lua_settable(m_L, -3);

    if  (parties == NULL) return;

    // if is the interaction event hanppend
    // push parties script name onto stack
    lua_pushstring(m_L, "partiesName");
    lua_pushstring(m_L, parties->getScriptName().c_str());
    lua_settable(m_L, -3);

    // push parties hash code onto stack
    lua_pushstring(m_L, "partiesHashCode");
    lua_pushstring(m_L, parties->getHashCode().c_str());
    lua_settable(m_L, -3);
}