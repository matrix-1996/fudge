#include <fudge/module.h>
#include <base/base.h>
#include <system/system.h>
#include "net.h"

static struct system_group root;

void net_register_interface(struct net_interface *interface)
{

}

void net_register_protocol(unsigned short index, struct net_protocol *protocol)
{

}

void net_unregister_interface(struct net_interface *interface)
{

}

void net_unregister_protocol(unsigned short index)
{

}

void net_init_interface(struct net_interface *interface, struct base_driver *driver, unsigned int (*send)(struct net_interface *self, unsigned int count, void *buffer))
{

    memory_clear(interface, sizeof (struct net_interface));

    interface->driver = driver;
    interface->send = send;


}

void net_init_protocol(struct net_protocol *protocol, char *name, unsigned int (*read)(struct net_interface *interface, unsigned int offset, unsigned int count, void *buffer), unsigned int (*write)(struct net_interface *interface, unsigned int offset, unsigned int count, void *buffer))
{

    memory_clear(protocol, sizeof (struct net_protocol));

    protocol->name = name;
    protocol->read = read;
    protocol->write = write;

}

void init()
{

    system_init_group(&root, "net");
    system_register_node(&root.node);

}

void destroy()
{

    system_unregister_node(&root.node);

}

