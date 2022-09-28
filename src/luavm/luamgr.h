#include "inc.h"
#include "libmgr.h"

#define getMgr(L) ((LuaMgr *)(((L)->stack+LUAVM_STACKNUMBER_MGR)->val.value_.p))

class LuaMgr
{
public:
    LuaMgr();
    ~LuaMgr();

public:
    inline LibMgr* getLibMgr() { return m_libMgr; };

private:
    lua_State* m_luaState;

    LibMgr* m_libMgr;
};

