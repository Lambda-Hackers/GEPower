#ifndef _COMMON_C_
#define _COMMON_C_
#include<windows.h>
#include<time.h>

/*--------------------------------------------------------------
* get correct to seconds from 1970-01-01 00:00:00 UTC, get time by
* C library
*/
time_t getRoughTime()
{
    return time(NULL);
}

#endif