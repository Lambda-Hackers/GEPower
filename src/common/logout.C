#include"logout.h"
#include<list>
#include<windows.h>
#include<algorithm>

struct logOutInfo
{
    logOutInfo(){};
    ~logOutInfo()
    {
        delete streamOut;
    }
    std::string path;
    Stream* streamOut;
};

namespace logOut
{
    std::list<logOutInfo*> m_outList;
    HANDLE m_logMutex = CreateMutex(NULL, false, NULL);
};

bool logOut::openStream(std::string path)
{
    WaitForSingleObjectEx(m_logMutex, INFINITE, false);
    for_each(m_outList.begin(), m_outList.end(), [&path](logOutInfo* logInfo){
        if (path == logInfo->path) {
            CloseHandle(m_logMutex);
            return;
        }
    });

    logOutInfo* info = new logOutInfo();
    info->path = path;
    info->streamOut = new Stream(path);

    m_outList.push_front(info);
    CloseHandle(m_logMutex);
    return true;

}

void logOut::closeStream()
{
    WaitForSingleObjectEx(m_logMutex, INFINITE, false);
    for_each(m_outList.begin(), m_outList.end(), [](logOutInfo* logInfo){
        m_outList.pop_front();
        delete logInfo;
    });
    CloseHandle(m_logMutex);
}

Stream* logOut::getStream()
{
    WaitForSingleObjectEx(m_logMutex, INFINITE, false);
    if (m_outList.empty())
    {
        CloseHandle(m_logMutex);
        return NULL; // std::cout;
    }
    CloseHandle(m_logMutex);
    return m_outList.front()->streamOut;
}