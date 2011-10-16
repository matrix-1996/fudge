#include <lib/memory.h>
#include <lib/string.h>
#include <kernel/vfs.h>
#include <kernel/modules.h>
#include <kernel/arch/x86/mmu.h>
#include <modules/elf/elf.h>
#include <kernel/runtime.h>

struct runtime_task runtimeTasks[8];

struct runtime_task *runtime_get_running_task()
{

    return &runtimeTasks[0];

}

unsigned int runtime_open_descriptor(struct runtime_task *task, char *path)
{

    struct vfs_node *node = vfs_find(path);

    if (!node)
        return -1;

    unsigned int i;

    for (i = 0; i < 16; i++)
    {

        if (!task->descriptors[i].node)
        {

            task->descriptors[i].node = node;
            task->descriptors[i].permissions = 0;

            return i;

        }

    }

    return -1;

}

void runtime_close_descriptor(struct runtime_task *task, unsigned int index)
{

    memory_set((void *)&task->descriptors[index], 0, sizeof (struct vfs_descriptor));

}

struct vfs_descriptor *runtime_get_descriptor(struct runtime_task *task, unsigned int index)
{

    return &task->descriptors[index];

}

void runtime_init()
{

}

