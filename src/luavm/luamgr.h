#include "inc.h"

class LuaMgr
{
public:
    LuaMgr();
    ~LuaMgr();

private:
    lua_State* m_luaState;
};

