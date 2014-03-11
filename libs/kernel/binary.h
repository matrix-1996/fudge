struct binary_protocol
{

    struct resource_item resource;
    unsigned int (*match)(struct vfs_channel *channel, unsigned int id);
    unsigned long (*find_symbol)(struct vfs_channel *channel, unsigned int id, unsigned int count, const char *symbol);
    unsigned long (*copy_program)(struct vfs_channel *channel, unsigned int id);
    unsigned int (*relocate)(struct vfs_channel *channel, unsigned int id, unsigned int address);

};

struct binary_protocol *binary_find_protocol(struct vfs_channel *channel, unsigned int id);
void binary_init_protocol(struct binary_protocol *protocol, unsigned int (*match)(struct vfs_channel *channel, unsigned int id), unsigned long (*find_symbol)(struct vfs_channel *channel, unsigned int id, unsigned int count, const char *symbol), unsigned long (*copy_program)(struct vfs_channel *channel, unsigned int id), unsigned int (*relocate)(struct vfs_channel *channel, unsigned int id, unsigned int address));
void binary_setup_elf(struct binary_protocol *protocol);
void binary_setup();
