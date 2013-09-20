#include <fudge.h>
#include "token.h"
#include "parse.h"

static unsigned int open_path(unsigned int index, unsigned int count, char *buffer)
{

    return memory_match(buffer, "/", 1) ? call_open(index, CALL_DR, count - 1, buffer + 1) : call_open(index, CALL_DW, count, buffer);

}

static void open_pipe(unsigned int index, unsigned int index0, unsigned int index1)
{

    char buffer[FUDGE_BSIZE];
    char num[32];
    unsigned int offset;
    unsigned int count = call_read(index, 0, 32, num);

    offset = memory_write(buffer, FUDGE_BSIZE, "system/pipe/", 12, 0);
    offset += memory_write(buffer, FUDGE_BSIZE, num, count, offset);
    offset += memory_write(buffer, FUDGE_BSIZE, "/0", 2, offset);

    call_open(index0, CALL_DR, offset, buffer);

    offset = memory_write(buffer, FUDGE_BSIZE, "system/pipe/", 12, 0);
    offset += memory_write(buffer, FUDGE_BSIZE, num, count, offset);
    offset += memory_write(buffer, FUDGE_BSIZE, "/1", 2, offset);

    call_open(index1, CALL_DR, offset, buffer);

}

static void execute_command(struct command *command, char *buffer)
{

    if (command->in0.path.count)
    {

        open_path(CALL_I0, command->in0.path.count, buffer + command->in0.path.index);

    }

    else if (command->in0.data.count)
    {

        call_open(CALL_L6, CALL_DR, 17, "system/pipe/clone");
        open_pipe(CALL_L6, CALL_L5, CALL_I0);
        call_write(CALL_L5, 0, command->in0.data.count, buffer + command->in0.data.index);

    }

    if (command->in1.path.count)
    {

        open_path(CALL_I1, command->in1.path.count, buffer + command->in1.path.index);

    }

    else if (command->in1.data.count)
    {

        call_open(CALL_L7, CALL_DR, 17, "system/pipe/clone");
        open_pipe(CALL_L7, CALL_L5, CALL_I1);
        call_write(CALL_L5, 0, command->in1.data.count, buffer + command->in1.data.index);

    }

    if (command->out0.path.count)
        open_path(CALL_O0, command->out0.path.count, buffer + command->out0.path.index);

    call_open(CALL_DW, CALL_DR, 4, "bin/");
    open_path(CALL_E0, command->binary.count, buffer + command->binary.index);
    call_open(CALL_DW, CALL_L3, 0, 0);
    call_spawn(CALL_E0);
    call_close(CALL_E0);

    if (command->in0.path.count)
        call_close(CALL_I0);
    else if (command->in0.data.count)
        call_close(CALL_L6);

    if (command->in1.path.count)
        call_close(CALL_I1);
    else if (command->in1.data.count)
        call_close(CALL_L7);

    if (command->out0.path.count)
        call_close(CALL_O0);

}

static void execute(struct token_state *state, struct expression *expression)
{

    unsigned int pindex;
    unsigned int cindex;

    call_open(CALL_L0, CALL_I0, 0, 0);
    call_open(CALL_L1, CALL_O0, 0, 0);
    call_open(CALL_L2, CALL_I1, 0, 0);
    call_open(CALL_L3, CALL_DW, 0, 0);

    for (pindex = 0; pindex < expression->count; pindex++)
    {

        struct pipe *pipe = &expression->pipes[pindex];

        for (cindex = 0; cindex < pipe->count - 1; cindex++)
            call_open(CALL_P0 + cindex, CALL_DR, 17, "system/pipe/clone");

        for (cindex = 0; cindex < pipe->count - 1; cindex++)
        {

            open_pipe(CALL_P0 + cindex, CALL_O0, 0);
            execute_command(&pipe->commands[cindex], state->buffer);
            open_pipe(CALL_P0 + cindex, 0, CALL_I0);

        }

        for (cindex = 0; cindex < pipe->count - 1; cindex++)
            call_close(CALL_P0 + cindex);

        call_open(CALL_O0, CALL_L1, 0, 0);
        execute_command(&pipe->commands[pipe->count - 1], state->buffer);

    }

    call_close(CALL_L0);
    call_close(CALL_L1);
    call_close(CALL_L2);
    call_close(CALL_L3);

}

void main()
{

    char buffer[FUDGE_BSIZE];
    struct token_state state;
    struct expression expression;

    memory_clear(&expression, sizeof (struct expression));
    token_init_state(&state, call_read(CALL_I0, 0, FUDGE_BSIZE, buffer), buffer);

    if (parse(&state, &expression))
        execute(&state, &expression);

}

