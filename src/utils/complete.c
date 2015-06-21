#include <abi.h>
#include <fudge.h>

void main()
{

    unsigned char buffer[FUDGE_BSIZE];
    unsigned int count0, count1, roff0, roff1, woff = 0;
    unsigned char kbuffer[FUDGE_BSIZE];
    unsigned int kcount;

    call_open(CALL_P1);

    kcount = call_read(CALL_P1, 0, 1, FUDGE_BSIZE, kbuffer);

    call_close(CALL_P1);
    call_open(CALL_PO);
    call_open(CALL_P0);
 
    for (roff0 = 0; (count0 = call_read(CALL_P0, roff0, 1, FUDGE_BSIZE, buffer)); roff0 += roff1)
    {

        for (roff1 = 0; (count1 = memory_findbyte(buffer + roff1, count0 - roff1, '\n')); roff1 += count1)
        {

            if (count1 < kcount)
                continue;

            if (!memory_match(buffer + roff1, kbuffer, kcount))
                continue;

            woff += call_write(CALL_PO, woff, count1, 1, buffer + roff1);

        }

    }

    call_close(CALL_P0);
    call_close(CALL_PO);

}
