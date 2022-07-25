#include "luamgr.h"

#include "event.h"

using namespace std;

static LuaMgr* luaMgr;

/* 全局日志输出对象 */
LogStream* g_logClass = NULL;

bool initOutPut()
{
    // initialization log
    g_logClass = logOut::openStream("../log/run.log");
    return true;
}

static void onTimeout(long long int fd, short int ev, void *arg)
{
    printf("into timeout callback!\n");
}

int main()
{
    initOutPut();
    error("<--------------lua begin---------------->");
#ifdef WIN32
    WSADATA wsa_data;
    WSAStartup(0x0201, &wsa_data);
#endif

#ifdef LIBEVENT_DEBUG
    event_enable_debug_mode();
#endif

    event_base* base = event_base_new();

	event* evtimer = event_new(base, -1, EV_PERSIST, onTimeout, NULL);
	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	event_add(evtimer, &tv); 

    luaMgr = new LuaMgr();
    while (true)
    {
        event_base_loop(base, EVLOOP_ONCE);
    }

    event_base_free(base);

    return 0;
}