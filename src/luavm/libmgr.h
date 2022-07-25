#include "inc.h"

class LibMgr
{
public:
    LibMgr();
    ~LibMgr();

private:

    bool openDll(const char* libname);
};