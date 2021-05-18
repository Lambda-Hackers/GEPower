#include<iterator>
#include<algorithm>
#include "LuaMgr.h"

using namespace std;
LuaMgr::LuaMgr()
{
    // Load main Lua scrite
    LuaVm* vm = new LuaVm(MAIN_LUA_PATH);
    if (vm && vm->initLuaVm())
    {
        m_vm.push_back(vm);
        out("create main vm thread OK");
    }
    else
    {
        out("create main thread failed, please check resource")
        return;
    }
    
}

LuaMgr::~LuaMgr()
{
}

/*--------------------------------------------------------------
* management interface for Lua Manager, use to control all LuaVm
*/
void LuaMgr::monLuaMgr()
{
    for_each(m_vm.begin(), m_vm.end(), [](auto it){
        
    });
}