#ifndef _LUAVM_SCRIPT_H_
#define _LUAVM_SCRIPT_H_

#include<string>
#include<map>
#include"wedge.h"
using namespace std;
struct funcCall {

};

class Script
{
public:
    Script(lua_State* l);
    ~Script();
public:
    inline void setScriptName(string name){
        m_scrpteName = name;
    }
    inline string& getScriptName(){
        return m_scrpteName;
    }
    inline string& getHashCode(){
        return m_hashcode;
    }
public:
    void crash(void* p);
    bool setEvent(const int& name, const int& func);
private:
    string m_scrpteName;
    lua_State* m_L;
    string m_hashcode;
private:
    void setTableValue(Script* parties = NULL);
};

#endif
