#ifndef __LOGGER_H__
#define __LOGGER_H__
// author : palanceli.blog.163.com

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define Logging        CLogger(__FILE__, __LINE__).Log


class CLogger
{
public:    

    CLogger(const char *fileName, int lineNo)
        : mFileName(fileName), mLineNo(lineNo)
    {	
        const char* p = strchr(mFileName, '/');
        if(p != 0)
            mFileName = p + 1;
    }

    void __cdecl Log(const char* pszFmt, ...) const
	{
	    va_list ptr; 
	    va_start(ptr, pszFmt);
	    char msg[512] = {0};
	    vsnprintf(msg, 512, pszFmt, ptr);
	    va_end(ptr);
	    printf("[%s:%d] %s\n", mFileName, mLineNo, msg);
	}

private:

    CLogger &__cdecl operator=(const CLogger &right);

    const char* mFileName;
    const int mLineNo;
};

#endif
