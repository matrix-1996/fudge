#include <fudge.h>
#include <kernel.h>
#include <modules/system/system.h>
#include "block.h"

static unsigned int wait;

void block_notify(struct block_interface *interface, unsigned int size, unsigned int count, void *buffer)
{

    system_write(&interface->data, 0, size, count, buffer);

    wait = 0;

}

static unsigned int interfacedata_read(struct system_node *self, unsigned int offset, unsigned int size, unsigned int count, void *buffer)
{

    struct block_interface *interface = self->resource->data;

    if (offset > 512)
        return 0;

    if (wait == 0)
    {

        interface->rdata(offset, size, count, buffer);
        wait = 1;

    }

    return scheduler_rmessage(scheduler_findactive(), size, count, buffer);

}

void block_registerinterface(struct block_interface *interface, unsigned int id)
{

    resource_register(&interface->resource);
    system_addchild(&interface->root, &interface->data);
    system_registernode(&interface->root);

    interface->id = id;

}

void block_unregisterinterface(struct block_interface *interface)
{

    resource_unregister(&interface->resource);
    system_removechild(&interface->root, &interface->data);
    system_unregisternode(&interface->root);

}

void block_initinterface(struct block_interface *interface, unsigned int (*rdata)(unsigned int offset, unsigned int size, unsigned int count, void *buffer), unsigned int (*wdata)(unsigned int offset, unsigned int size, unsigned int count, void *buffer))
{

    resource_init(&interface->resource, RESOURCE_BLOCKINTERFACE, interface);
    system_initnode(&interface->root, SYSTEM_NODETYPE_GROUP | SYSTEM_NODETYPE_MULTI, "block");
    system_initnode(&interface->data, SYSTEM_NODETYPE_MAILBOX, "data");

    interface->rdata = rdata;
    interface->wdata = wdata;
    interface->data.resource = &interface->resource;
    interface->data.read = interfacedata_read;

}
