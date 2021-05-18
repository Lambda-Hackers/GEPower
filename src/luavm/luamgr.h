#include"wedge.C"
#include"luavm.h"

#include<vector>
using namespace std;

class LuaMgr
{
public:
    LuaMgr();
    ~LuaMgr();
    // management interface for Lua Manager
    void monLuaMgr();
private:
    // store all vm, this frist solt is a vm for main Lua scipte.
    vector<LuaVm *> m_vm;
};

