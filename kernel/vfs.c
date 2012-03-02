#include <lib/memory.h>
#include <lib/string.h>
#include <kernel/vfs.h>

static struct vfs_filesystem *filesystems[VFS_FILESYSTEM_SLOTS];

void vfs_register_filesystem(struct vfs_filesystem *filesystem)
{

    unsigned int i;

    for (i = 0; i < VFS_FILESYSTEM_SLOTS; i++)
    {

        if (filesystems[i])
            continue;

        filesystems[i] = filesystem;

        break;

    }

}

struct vfs_filesystem *vfs_get_filesystem(unsigned int index)
{

    if (!filesystems[index])
        return 0;

    return filesystems[index];

}

struct vfs_filesystem *vfs_find_filesystem(char *path)
{

    if (!string_length(path))
        return 0;

    unsigned int i;

    for (i = 0; i < VFS_FILESYSTEM_SLOTS; i++)
    {

        if (!filesystems[i])
            continue;

        struct vfs_filesystem *filesystem = filesystems[i];

        unsigned int index = filesystem->find_node(filesystem, path);

        if (!index)
            continue;

        return filesystem;

    }

    return 0;

}

void vfs_node_init(struct vfs_node *node, char *name, unsigned int (*read)(struct vfs_node *self, unsigned int count, void *buffer), unsigned int (*write)(struct vfs_node *self, unsigned int count, void *buffer))
{

    memory_clear(node, sizeof (struct vfs_node));

    string_write(node->name, name);
    node->read = read;
    node->write = write;

}

void vfs_filesystem_init(struct vfs_filesystem *filesystem, char *name, unsigned int firstIndex, void (*open)(struct vfs_filesystem *self, unsigned int index), void (*close)(struct vfs_filesystem *self, unsigned int index), unsigned int (*read)(struct vfs_filesystem *self, unsigned int index, unsigned int count, void *buffer), unsigned int (*write)(struct vfs_filesystem *self, unsigned int index, unsigned int count, void *buffer), char *(*get_name)(struct vfs_filesystem *self, unsigned int index), unsigned int (*find_node)(struct vfs_filesystem *self, char *name), unsigned int (*walk)(struct vfs_filesystem *self, unsigned int index), void *(*get_physical)(struct vfs_filesystem *self, unsigned int index))
{

    memory_clear(filesystem, sizeof (struct vfs_filesystem));

    filesystem->name = name;
    filesystem->firstIndex = firstIndex;
    filesystem->open = open;
    filesystem->close = close;
    filesystem->read = read;
    filesystem->write = write;
    filesystem->get_name = get_name;
    filesystem->find_node = find_node;
    filesystem->walk = walk;
    filesystem->get_physical = get_physical;

}

