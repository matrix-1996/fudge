#include <fudge.h>
#include "resource.h"
#include "vfs.h"
#include "binary.h"
#include "task.h"

static struct list active;
static struct list inactive;
static struct list blocked;

struct task *task_findactive(void)
{

    return (active.tail) ? active.tail->data : 0;

}

struct task_mailbox *task_findactivemailbox(void)
{

    struct task *task = task_findactive();

    if (task)
        return &task->mailbox;

    return 0;

}

struct task *task_findinactive(void)
{

    return (inactive.tail) ? inactive.tail->data : 0;

}

void task_setstatus(struct task *task, unsigned int status)
{

    switch (status)
    {

    case TASK_STATUS_INACTIVE:
        list_move(&inactive, &task->state.item);

        task->state.status = TASK_STATUS_INACTIVE;

        break;

    case TASK_STATUS_ACTIVE:
        list_move(&active, &task->state.item);

        task->state.status = TASK_STATUS_ACTIVE;

        break;

    case TASK_STATUS_BLOCKED:
        if (task->state.status != TASK_STATUS_ACTIVE)
            break;

        list_move(&blocked, &task->state.item);

        task->state.status = TASK_STATUS_BLOCKED;

        break;

    case TASK_STATUS_UNBLOCKED:
        if (task->state.status != TASK_STATUS_BLOCKED)
            break;

        list_move(&active, &task->state.item);

        task->state.status = TASK_STATUS_UNBLOCKED;

        break;

    }

}

void task_resume(struct task *task, unsigned int ip, unsigned int sp)
{

    if (task->state.status != TASK_STATUS_UNBLOCKED)
        return;

    task->state.status = TASK_STATUS_ACTIVE;
    task->state.registers.ip = ip;
    task->state.registers.sp = sp;

}

void task_copydescriptors(struct task *source, struct task *target)
{

    unsigned int i;

    for (i = 0x00; i < 0x08; i++)
    {

        target->descriptors[i + 0x00].channel = source->descriptors[i + 0x08].channel;
        target->descriptors[i + 0x00].id = source->descriptors[i + 0x08].id;
        target->descriptors[i + 0x00].offset = 0;
        target->descriptors[i + 0x08].channel = source->descriptors[i + 0x08].channel;
        target->descriptors[i + 0x08].id = source->descriptors[i + 0x08].id;
        target->descriptors[i + 0x08].offset = 0;
        target->descriptors[i + 0x10].channel = 0;
        target->descriptors[i + 0x10].id = 0;
        target->descriptors[i + 0x10].offset = 0;
        target->descriptors[i + 0x18].channel = 0;
        target->descriptors[i + 0x18].id = 0;
        target->descriptors[i + 0x18].offset = 0;

    }

}

unsigned int task_initbinary(struct task *task, unsigned int sp)
{

    struct task_descriptor *descriptor = &task->descriptors[0];

    if (!descriptor->id || !descriptor->channel)
        return 0;

    task->format = binary_findformat(descriptor->channel, descriptor->id);

    if (!task->format)
        return 0;

    task->state.registers.ip = task->format->findentry(descriptor->channel, descriptor->id);
    task->state.registers.sp = sp;

    return task->state.registers.ip;

}

void task_register(struct task *task)
{

    list_add(&inactive, &task->state.item);

}

void task_unregister(struct task *task)
{

    list_remove(&inactive, &task->state.item);

}

void task_initdescriptor(struct task_descriptor *descriptor)
{

    resource_init(&descriptor->resource, RESOURCE_TASKDESCRIPTOR, descriptor);

}

void task_initmailbox(struct task_mailbox *mailbox, struct task *task)
{

    list_inititem(&mailbox->item, mailbox);
    buffer_init(&mailbox->buffer, TASK_MAILBOXSIZE, mailbox->data);

    mailbox->task = task;

}

void task_init(struct task *task)
{

    unsigned int i;

    resource_init(&task->resource, RESOURCE_TASK, task);
    list_inititem(&task->state.item, task);
    task_initmailbox(&task->mailbox, task);

    for (i = 0; i < TASK_DESCRIPTORS; i++)
        task_initdescriptor(&task->descriptors[i]);

}

