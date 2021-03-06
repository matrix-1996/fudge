#include "memory.h"

void memory_clear(void *out, unsigned int count)
{

    unsigned char *op = out;

    while (count--)
        *op++ = 0;

}

void memory_copy(void *out, void *in, unsigned int count)
{

    unsigned char *op = out;
    unsigned char *ip = in;

    while (count--)
        *op++ = *ip++;

}

unsigned int memory_findbyte(void *in, unsigned int count, char value)
{

    unsigned char *ip = in;
    unsigned int offset;

    if (!count)
        return 0;

    for (offset = 1; offset < count && ip[offset - 1] != value; offset++);

    return offset;

}

unsigned int memory_match(void *in1, void *in2, unsigned int count)
{

    unsigned char *ip1 = in1;
    unsigned char *ip2 = in2;

    while (count--)
    {

        if (*ip1++ != *ip2++)
            return 0;

    }

    return 1;

}

unsigned int memory_read(void *out, unsigned int ocount, void *in, unsigned int icount, unsigned int offset)
{

    unsigned char *op = out;
    unsigned char *ip = in;

    if (offset >= icount)
        return 0;

    if (ocount > icount - offset)
        ocount = icount - offset;

    memory_copy(op, ip + offset, ocount);

    return ocount;

}

unsigned int memory_write(void *out, unsigned int ocount, void *in, unsigned int icount, unsigned int offset)
{

    unsigned char *op = out;
    unsigned char *ip = in;

    if (offset >= ocount)
        return 0;

    if (icount > ocount - offset)
        icount = ocount - offset;

    memory_copy(op + offset, ip, icount);

    return icount;

}

