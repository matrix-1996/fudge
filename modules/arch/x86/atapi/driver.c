#include <fudge/module.h>
#include <base/base.h>
#include <block/block.h>
#include <arch/x86/ide/ide.h>
#include <arch/x86/pic/pic.h>
#include "atapi.h"

static void handle_irq(struct base_device *device)
{

}

static void attach(struct base_device *device)
{

    pic_set_routine(device, handle_irq);

}

static unsigned int check(struct base_device *device)
{

    struct ide_device *ideDevice = (struct ide_device *)device;

    if (device->type != IDE_DEVICE_TYPE)
        return 0;

    return ideDevice->type == IDE_DEVICE_TYPE_ATAPI;

}

void atapi_init_driver(struct atapi_driver *driver)
{

    memory_clear(driver, sizeof (struct atapi_driver));
    base_init_driver(&driver->base, "atapi", check, attach);
    block_init_interface(&driver->iblock, &driver->base, 0, 0);

}

