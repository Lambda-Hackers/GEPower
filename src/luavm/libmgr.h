#ifndef _LUA_LIBMGR_
#define _LUA_LIBMGR_

#include "inc.h"

#include <unordered_map>
#include <string>

class LibDll
{
public:
    LibDll(const char* libname);
    ~LibDll();
};

class LibMgr
{
public:
    LibMgr();
    ~LibMgr();

    bool l_include(const char* libname);

private:
    bool openDll(const char* libname);
    bool openLua(const char* libname);

private:
    // management all dll to lua
    std::unordered_map<std::string, LibDll*> m_dllmgr;
};

#endif