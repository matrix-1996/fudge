struct block_interface
{

    struct base_driver *driver;
    unsigned int (*read_data)(struct block_interface *self, unsigned int offset, unsigned int count, void *buffer);
    unsigned int (*write_data)(struct block_interface *self, unsigned int offset, unsigned int count, void *buffer);

};

struct block_protocol
{

    char *name;

};

struct block_filesystem
{

    struct vfs_interface base;
    struct block_interface *interfaces[8];
    unsigned int interfacesCount;
    struct block_protocol *protocols[16];
    unsigned int protocolsCount;

};

void block_register_interface(struct block_interface *interface);
void block_register_protocol(struct block_protocol *protocol);
void block_unregister_interface(struct block_interface *interface);
void block_unregister_protocol(struct block_protocol *protocol);
void block_init_filesystem(struct block_filesystem *filesystem);
void block_init_interface(struct block_interface *interface, struct base_driver *driver);
