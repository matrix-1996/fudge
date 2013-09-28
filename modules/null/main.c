#include <fudge/module.h>
#include <kernel/vfs.h>
#include <system/system.h>
#include <base/base.h>

static struct system_stream root;

void init()
{

    system_init_stream(&root, "null");
    system_register_node(&root.node);

}

void destroy()
{

    system_unregister_node(&root.node);

}

