#include <kernel.h>
#include "resource.h"
#include "vfs.h"
#include "task.h"

void task_initmailbox(struct task_mailbox *mailbox)
{

    list_inititem(&mailbox->item, mailbox);
    buffer_init(&mailbox->buffer, 1, 4096, mailbox->data);

}

void task_init(struct task *task, unsigned long ip, unsigned long sp)
{

    unsigned int i;

    list_inititem(&task->item, task);
    resource_init(&task->resource, RESOURCE_TYPE_TASK, task);
    task_initmailbox(&task->mailbox);

    for (i = 0; i < TASK_DESCRIPTORS; i++)
        vfs_initdescriptor(&task->descriptors[i]);

    task->registers.ip = ip;
    task->registers.sp = sp;

}

