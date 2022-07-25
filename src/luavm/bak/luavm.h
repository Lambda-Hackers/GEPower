#include <string>
#include"wedge.h"

using namespace std;

class LuaVm
{
public:
    LuaVm(string path);
    ~LuaVm();
    // initialization func for LuaVm
    bool initLuaVm();
public:
    inline lua_State* L(){return m_L;};
private:
    // main Lua State for this Vm
    lua_State* m_L;
    // Lua Script's Path
    string m_scriptPath;
};