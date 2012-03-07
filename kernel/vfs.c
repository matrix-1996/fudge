#include <lib/memory.h>
#include <lib/string.h>
#include <kernel/vfs.h>
#include <kernel/vfs/ramdisk.h>
#include <kernel/vfs/root.h>
#include <kernel/vfs/sys.h>

struct vfs_filesystem *filesystems[VFS_FILESYSTEM_SLOTS];
struct vfs_mount mounts[VFS_MOUNT_SLOTS];

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

struct vfs_mount *vfs_find_mount(char *path)
{

    struct vfs_mount *current = 0;
    unsigned int max = 0;

    unsigned int i;

    for (i = 0; i < VFS_MOUNT_SLOTS; i++)
    {

        if (!mounts[i].filesystem)
            continue;

        unsigned int length = string_length(mounts[i].path);

        if (memory_compare(mounts[i].path, path, length))
            continue;

        if (length < max)
            continue;

        current = &mounts[i];
        max = length;

    }

    return current;


}

void vfs_mount(struct vfs_filesystem *filesystem, char *path)
{

    unsigned int i;

    for (i = 0; i < VFS_MOUNT_SLOTS; i++)
    {

        if (mounts[i].filesystem)
            continue;

        vfs_mount_init(&mounts[i], filesystem, path);

        break;

    }

};

void vfs_filesystem_init(struct vfs_filesystem *filesystem, void (*open)(struct vfs_filesystem *self, unsigned int id), void (*close)(struct vfs_filesystem *self, unsigned int id), unsigned int (*read)(struct vfs_filesystem *self, unsigned int id, unsigned int offset, unsigned int count, void *buffer), unsigned int (*write)(struct vfs_filesystem *self, unsigned int id, unsigned int offset, unsigned int count, void *buffer), unsigned int (*find)(struct vfs_filesystem *self, char *path), void *(*get_physical)(struct vfs_filesystem *self, unsigned int id))
{

    memory_clear(filesystem, sizeof (struct vfs_filesystem));

    filesystem->open = open;
    filesystem->close = close;
    filesystem->read = read;
    filesystem->write = write;
    filesystem->find = find;
    filesystem->get_physical = get_physical;

}

void vfs_mount_init(struct vfs_mount *mount, struct vfs_filesystem *filesystem, char *path)
{

    mount->filesystem = filesystem;
    mount->path = path;

}

void vfs_init()
{

    vfs_root_init();
    vfs_sys_init();
    vfs_ramdisk_init();

}

