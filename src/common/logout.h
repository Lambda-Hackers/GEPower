#ifndef _COMMON_LOGOUT_H_
#define _COMMON_LOGOUT_H_
#include <stdio.h>
#include <string.h>
#include <windows.h>

#ifdef GEPOWER_STDERR
#define outToStderr(...) fprintf(stderr, __VA_ARGS__)
#else
#define outToStderr(...) void()
#endif

/*
    输出日志级别
*/
enum LOG_OUT_CLASS
{
    LOG_DEBUG, // 调试
    LOG_INFO,  // 提示
    LOG_WARN,  // 警告
    LOG_ERROR
};

/*
    输出流对象，线程安全
*/
class LogStream
{
public:
    LogStream(const char* logPath):m_logOutClass(LOG_DEBUG) {
        m_fileDescripte = fopen(logPath, "w+");
        m_logMutex = CreateMutex(NULL, false, NULL);
    }

    ~LogStream() {
        fclose(m_fileDescripte);
        ReleaseMutex(m_logMutex);
    }

    void outf(LOG_OUT_CLASS outClass, const char* context) {
        /* 检查是否符合最低输出级别 */
        if (outClass < m_logOutClass)
            return;

        WaitForSingleObjectEx(m_logMutex, INFINITE, false);
        fprintf(m_fileDescripte, context);
        CloseHandle(m_logMutex);
    }
    void outf(LOG_OUT_CLASS outClass, const char* format, va_list va)
    {
        /* 检查是否符合最低输出级别 */
        if (outClass < m_logOutClass)
            return;

        WaitForSingleObjectEx(m_logMutex, INFINITE, false);
        if (vfprintf(m_fileDescripte, format, va))
            outToStderr("failed to write format log\n");
        fflush(m_fileDescripte);
        CloseHandle(m_logMutex);
    }

private:
    FILE* m_fileDescripte;
    HANDLE m_logMutex;

    /* 当前流的最低输出级别 */
    LOG_OUT_CLASS m_logOutClass;
};

namespace logOut
{
    LogStream* openStream(const char* path);

    // try to close log, no error(if something error just ignored)
    void closeStream(LogStream* stream);

    // write context to the file
    void outf(LogStream* stream, LOG_OUT_CLASS outClass, const char* context);
    void outv(LogStream* stream, LOG_OUT_CLASS outClass, const char *format, ...);
};

extern LogStream* g_logClass;

#define debug(...) logOut::outv(g_logClass, LOG_DEBUG, __VA_ARGS__)
#define info(...)  logOut::outv(g_logClass, LOG_DEBUG, __VA_ARGS__)
#define warn(...)  logOut::outv(g_logClass, LOG_DEBUG, __VA_ARGS__)
#define error(...) logOut::outv(g_logClass, LOG_DEBUG, __VA_ARGS__)
#endif