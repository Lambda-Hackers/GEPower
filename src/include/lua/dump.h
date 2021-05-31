#ifndef _INCLUDE_DUMP_H_
#define _INCLUDE_DUMP_H_
#include<string>
#include"lua.h"
using namespace std;

extern void dumpstack(lua_State* L, const string& str = NULL);

#endif