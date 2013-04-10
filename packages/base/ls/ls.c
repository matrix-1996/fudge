#include <fudge.h>

void main()
{

    char buffer[FUDGE_BSIZE];
    unsigned int offset;
    unsigned int count;

    for (offset = 0; (count = call_read(FUDGE_DW, offset, FUDGE_BSIZE, buffer)); offset += count)
        call_write(FUDGE_DO, offset, count, buffer);

}

