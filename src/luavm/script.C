
#include"script.h"

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

// script deal msg crash fun
void Script::crash()
{
    
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