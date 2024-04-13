#include <iostream>
#include "zpeslib.h"

bool ZPESFILE::Read(const char* imputFile)
{
    // Check src
    if (src != nullptr)
        return false;

    // Open the file
    FILE* file = fopen(imputFile, "rb");
    if (file == nullptr)
        return false;

    fstat(_fileno(file), &st);
    src = (BYTE*)malloc(st.st_size);
    if (src == nullptr)
    {
        fclose(file);
        return false;
    }
    fread(src, st.st_size, 1, file);
    fclose(file);
    readed = true;
    return true;
}

bool ZPESFILE::Uncompress()
{
    // Check if file was readed
    if (!readed)
        return false;


    srcLen = *(uLongf*)(src + 0x0c);
    BYTE* temp = (BYTE*)malloc(srcLen); // big enough buffer

    int retval = uncompress(temp, &srcLen, src + 0x10, srcLen - 0x10);
    if (retval != Z_OK)
    {
        free(temp);
        return false;
    }

    free(src);
    src = temp;
    return true;
}

bool ZPESFILE::Compress()
{
    // Check if file was readed
    if (!readed)
        return false;

    if (srcLen == 0)
        srcLen = st.st_size;

    uLong tempLen = srcLen * 2;
    BYTE* temp = (BYTE*)malloc(tempLen); // big buffer just in case;
    int retval = compress(temp, &tempLen, src, srcLen);
    if (retval != Z_OK)
    {
        free(temp);
        return false;
    }

    free(src);
    src = temp;
    srcLen = tempLen;
    return true;
}

void* ZPESFILE::GetBuffer()
{
    return src;
}

bool ZPESFILE::Write(const char* outputFile, ZFLAG flag)
{
    // Check if file was readed
    if (!readed)
        return false;

    // Check if file was manipulate
    if (srcLen == 0)
        return false;

    FILE* outf = fopen(outputFile, "wb");
    if (!outf)
        return false;

    if (flag == COMPRESSED)
    {
        fwrite("\x00\x01\x01WESYS", 8, 1, outf);
        fwrite(&srcLen, sizeof(uLongf), 1, outf);
        srcLen *= 2;
        fwrite(&srcLen, sizeof(uLongf), 1, outf);
        srcLen /= 2;
    }
    fwrite(src, srcLen, 1, outf);
    fclose(outf);
}

ZPESFILE::~ZPESFILE()
{
    if (src != nullptr)
        free(src);
}