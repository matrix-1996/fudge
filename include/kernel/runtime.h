#ifndef KERNEL_RUNTIME_H
#define KERNEL_RUNTIME_H

struct runtime_task
{

    struct mmu_header *header;
    struct vfs_descriptor descriptors[16];

};

extern struct runtime_task *runtime_get_running_task();
extern unsigned int runtime_open_descriptor(struct runtime_task *task, char *path);
extern void runtime_close_descriptor(struct runtime_task *task, unsigned int index);
extern struct vfs_descriptor *runtime_get_descriptor(struct runtime_task *task, unsigned int index);
extern void runtime_init();

#endif

