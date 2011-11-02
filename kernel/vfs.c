#include <lib/memory.h>
#include <lib/string.h>
#include <kernel/vfs.h>

static struct vfs_filesystem *vfsFilesystems[VFS_FILESYSTEM_MAX];
static struct vfs_filesystem vfsFilesystem;
static struct vfs_node vfsRoot;

void vfs_register_filesystem(struct vfs_filesystem *filesystem)
{

    unsigned int i;

    for (i = 0; i < VFS_FILESYSTEM_MAX; i++)
    {

        if (vfsFilesystems[i])
            continue;

        vfsFilesystems[i] = filesystem;

        return;

    }

}

struct vfs_node *vfs_find(char *path)
{

    if (path[0] != '/')
        return 0;

    if (string_length(path) == 1)
        return vfsFilesystem.root;

    unsigned int i;

    for (i = 0; vfsFilesystems[i]; i++)
    {

        struct vfs_node *node = vfsFilesystems[i]->lookup(vfsFilesystems[i], path + 1);

        if (node)
            return node;

    }

    return 0;

}

static struct vfs_node *vfs_filesystem_lookup(struct vfs_filesystem *self, char *path)
{

    return 0;

}

static unsigned int vfs_filesystem_node_read(struct vfs_node *self, unsigned int count, void *buffer)
{

    memory_set(buffer, 0, 1);

    unsigned int i;

    for (i = 0; vfsFilesystems[i]; i++)
    {

        if (vfsFilesystems[i] == &vfsFilesystem)
            continue;

        vfsFilesystems[i]->root->read(vfsFilesystems[i]->root, count, buffer + string_length(buffer));

    }

    return string_length(buffer);

}

void vfs_filesystem_init(struct vfs_filesystem *filesystem, struct vfs_node *root, struct vfs_node *(*lookup)(struct vfs_filesystem *self, char *path))
{

    filesystem->root = root;
    filesystem->lookup = lookup;

}

void vfs_init()
{

    vfsRoot.read = vfs_filesystem_node_read;

    vfs_filesystem_init(&vfsFilesystem, &vfsRoot, vfs_filesystem_lookup);
    vfs_register_filesystem(&vfsFilesystem);

}

