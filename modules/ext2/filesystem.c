#include <lib/memory.h>
#include <lib/string.h>
#include <kernel/vfs.h>
#include <kernel/modules.h>
#include <modules/ext2/ext2.h>

static struct ext2_driver *driver;
static struct vfs_filesystem filesystem;

static unsigned int read(struct vfs_filesystem *self, unsigned int id, unsigned int offset, unsigned int count, void *buffer)
{

    char mem[1024];
    char *private = mem;

    driver->read_node(driver, id, private);

    unsigned int c = 0;

    for (;;)
    {

        struct ext2_directory *directory = (struct ext2_directory *)private;

        if (!directory->length)
            return c;

        memory_copy(buffer + c, private + 8, directory->length);
        memory_copy(buffer + c + directory->length, "\n", 1);
        c += directory->length + 1;

        private += directory->size;

    }

    return c;

}

static unsigned int find(struct vfs_filesystem *self, char *name)
{

    unsigned int length = string_length(name);

    if (!length)
        return 2;

    return 0;

}

void ext2_filesystem_init(struct modules_module *module)
{

    driver = (struct ext2_driver *)module;

    vfs_filesystem_init(&filesystem, 0, 0, read, 0, find, 0); 
    vfs_mount(&filesystem, "/hda/");

}

