#include"event.h"

static HANDLE handle;

static EventInfo* g_event;

struct msgInfo
{
    msgInfo(CALLBAK func, void* argt)
    {
        m_func = func;
        m_argt = argt;
    }

    CALLBAK m_func;
    void* m_argt;
};


class EventInfo
{
public:
    EventInfo();
    bool addEventMsg(CALLBAK func, void* argt);
    bool doEventMsg();
    inline bool isEmpty()
    {
        return (m_begin == m_end);
    }
private:
    std::vector<msgInfo> m_eventQue[_MAX_EVENT_NUM_];
    unsigned int m_begin;
    unsigned int m_end;

private:
    void doCallBack(const int num);
};

EventInfo::EventInfo()
{
    m_begin = 0;
    m_end = 0;
}

/*--------------------------------------------------------------
* add event to the vector by the callbak func and it's argt
*/
bool EventInfo::addEventMsg(CALLBAK func, void* argt)
{
    if ((m_end + 1) % _MAX_EVENT_NUM_ == m_begin)
    {
        // full events not to get more
        return false;
    }
    m_end = (m_end + 1) % _MAX_EVENT_NUM_;
    m_eventQue->at(m_end).m_argt = argt;
    m_eventQue->at(m_end).m_func = func;

    return true;
}

void EventInfo::doCallBack(const int num)
{
    // do callback func
    m_eventQue->at(num).m_func(m_eventQue->at(num).m_argt);
}

bool EventInfo::doEventMsg()
{
    while (m_begin != m_end)
    {
        doCallBack(m_begin);
        m_begin = (m_begin + 1) % _MAX_EVENT_NUM_;
    }
    return true;
}

bool WINEVENT::createEvent()
{
    g_event = new EventInfo();
    handle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 1);
    return handle == NULL ? false : true;
}

void WINEVENT::eventLoop(DWORD waitTime)
{
    DWORD num = 0;
    GetQueuedCompletionStatus(handle, &num, NULL, NULL, waitTime);
    if (num > 0) 
    {
        g_event->doEventMsg();
    }
    // sleep(waitTime);
}

bool WINEVENT::addEvent(CALLBAK callbak, void* argt)
{
    return g_event->addEventMsg(callbak, argt);
}