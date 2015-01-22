#include <fudge.h>
#include <kernel.h>
#include <system/system.h>
#include <base/base.h>
#include <event/event.h>
#include "console.h"

static struct list mailboxes;
static struct system_node root;

void console_notify(unsigned int count, void *buffer)
{

    struct list_item *current;

    for (current = mailboxes.head; current; current = current->next)
    {

        struct task_mailbox *mailbox = current->data;

        scheduler_mailbox_write(mailbox, count, buffer);

    }

    event_notify(EVENT_TYPE_CONSOLE, count, buffer);

}

static unsigned int interfacenode_ctrlread(struct system_node *self, unsigned int offset, unsigned int count, void *buffer)
{

    struct console_interfacenode *node = (struct console_interfacenode *)self->parent;

    return memory_read(buffer, count, &node->interface->settings, sizeof (struct ctrl_consolesettings), offset);

}

static unsigned int interfacenode_ctrlwrite(struct system_node *self, unsigned int offset, unsigned int count, void *buffer)
{

    struct console_interfacenode *node = (struct console_interfacenode *)self->parent;

    return memory_write(&node->interface->settings, sizeof (struct ctrl_consolesettings), buffer, count, offset);

}

static unsigned int interfacenode_dataopen(struct system_node *self)
{

    scheduler_activetask_addmailbox(&mailboxes);

    return system_open(self);

}

static unsigned int interfacenode_dataclose(struct system_node *self)
{

    scheduler_activetask_removemailbox(&mailboxes);

    return system_close(self);

}

static unsigned int interfacenode_dataread(struct system_node *self, unsigned int offset, unsigned int count, void *buffer)
{

    return scheduler_activetask_readmailbox(count, buffer);

}

static unsigned int interfacenode_datawrite(struct system_node *self, unsigned int offset, unsigned int count, void *buffer)
{

    struct console_interfacenode *node = (struct console_interfacenode *)self->parent;

    return node->interface->wdata(offset, count, buffer);

}

void console_registerinterface(struct console_interface *interface, struct base_bus *bus, unsigned int id)
{

    base_registerinterface(&interface->base, bus, id);
    system_addchild(&root, &interface->node.base);
    system_addchild(&interface->node.base, &interface->node.ctrl);
    system_addchild(&interface->node.base, &interface->node.data);

}

void console_unregisterinterface(struct console_interface *interface)
{

    base_unregisterinterface(&interface->base);
    system_removechild(&interface->node.base, &interface->node.ctrl);
    system_removechild(&interface->node.base, &interface->node.data);
    system_removechild(&root, &interface->node.base);

}

void console_initinterface(struct console_interface *interface, struct base_driver *driver, unsigned int (*wdata)(unsigned int offset, unsigned int count, void *buffer))
{

    base_initinterface(&interface->base, driver);
    system_initnode(&interface->node.base, SYSTEM_NODETYPE_GROUP | SYSTEM_NODETYPE_MULTI, driver->name);
    system_initnode(&interface->node.ctrl, SYSTEM_NODETYPE_NORMAL, "ctrl");
    system_initnode(&interface->node.data, SYSTEM_NODETYPE_NORMAL, "data");
    ctrl_init_consolesettings(&interface->settings);

    interface->wdata = wdata;
    interface->node.interface = interface;
    interface->node.ctrl.read = interfacenode_ctrlread;
    interface->node.ctrl.write = interfacenode_ctrlwrite;
    interface->node.data.open = interfacenode_dataopen;
    interface->node.data.close = interfacenode_dataclose;
    interface->node.data.read = interfacenode_dataread;
    interface->node.data.write = interfacenode_datawrite;

}

void init()
{

    list_init(&mailboxes);
    system_initnode(&root, SYSTEM_NODETYPE_GROUP, "console");
    system_registernode(&root);

}

void destroy()
{

    system_unregisternode(&root);

}

