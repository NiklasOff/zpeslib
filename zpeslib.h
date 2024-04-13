#ifndef _ZPESLIB_H
#define _ZPESLIB_H

#include <windows.h>
#include <zlib.h>
#include <sys/stat.h>

enum ZFLAG
{
    COMPRESSED,
    UNCOMPRESSED
};

class ZPESFILE
{
private:
    struct stat st;
    BYTE* src;
    uLong srcLen;
    bool readed;
public:
    ZPESFILE() :
        st({ 0 }),
        src(nullptr),
        srcLen(0),
        readed(false)
    {}
    bool Read(const char* imputFile);
    bool Uncompress();
    bool Compress();
    void* GetBuffer();
    uLong GetBufferSize();
    bool Write(const char* outputFile, ZFLAG flag);
    ~ZPESFILE();
};

#endif