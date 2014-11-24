#include <module.h>
#include <kernel/resource.h>
#include <kernel/scheduler.h>
#include <system/system.h>
#include <base/base.h>
#include <mouse/mouse.h>
#include <arch/x86/pic/pic.h>
#include <arch/x86/ps2/ps2.h>

static struct base_driver driver;
static struct mouse_interface mouseinterface;
static struct mouse_interfacenode mouseinterfacenode;
static unsigned char buffer[512];
static struct buffer cfifo;
static unsigned char cycle;
static struct scheduler_rendezvous rdata;

static void handleirq(unsigned int irq, struct base_bus *bus, unsigned int id)
{

    unsigned char data = ps2_getdata(bus);

    switch (cycle)
    {

    case 0:
        cycle++;

        break;

    case 1:
        cycle++;

        break;

    case 2:
        cycle = 0;

        break;

    }

    buffer_wcfifo(&cfifo, 1, &data);
    scheduler_rendezvous_unsleep(&rdata);

}

static unsigned int mouseinterface_rdata(unsigned int offset, unsigned int count, void *buffer)
{

    count = buffer_rcfifo(&cfifo, count, buffer);

    scheduler_rendezvous_sleep(&rdata, !count);

    return count;

}

static unsigned int driver_match(struct base_bus *bus, unsigned int id)
{

    if (bus->type != PS2_BUS_TYPE)
        return 0;

    return id == PS2_MOUSE_DEVICE_TYPE;

}

static void driver_attach(struct base_bus *bus, unsigned int id)
{

    mouse_initinterface(&mouseinterface, &driver, bus, id, mouseinterface_rdata);
    mouse_registerinterface(&mouseinterface);
    mouse_initinterfacenode(&mouseinterfacenode, &mouseinterface);
    mouse_registerinterfacenode(&mouseinterfacenode);
    buffer_init(&cfifo, 1, 512, &buffer);
    pic_setroutine(bus, id, handleirq);
    ps2_enable(bus, id);
    ps2_reset(bus, id);
    ps2_disablescanning(bus, id);
    ps2_default(bus, id);
    ps2_identify(bus, id);
    ps2_enablescanning(bus, id);
    ps2_enableinterrupt(bus, id);

}

static void driver_detach(struct base_bus *bus, unsigned int id)
{

    pic_unsetroutine(bus, id);
    mouse_unregisterinterface(&mouseinterface);
    mouse_unregisterinterfacenode(&mouseinterfacenode);

}

void init()
{

    base_initdriver(&driver, "ps2mouse", driver_match, driver_attach, driver_detach);
    base_registerdriver(&driver);

}

void destroy()
{

    base_unregisterdriver(&driver);

}
