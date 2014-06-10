#include <module.h>
#include <kernel/resource.h>
#include <kernel/rendezvous.h>
#include <base/base.h>
#include <base/timer.h>
#include <arch/x86/pic/pic.h>
#include <arch/x86/io/io.h>
#include <arch/x86/platform/platform.h>

#define PIT_FREQUENCY                   1193182
#define PIT_HERTZ                       1000

enum pit_register
{

    PIT_REGISTER_COUNTER0               = 0x00,
    PIT_REGISTER_COUNTER1               = 0x01,
    PIT_REGISTER_COUNTER2               = 0x02,
    PIT_REGISTER_COMMAND                = 0x03

};

enum pit_command
{

    PIT_COMMAND_BINARY                  = 0x00,
    PIT_COMMAND_BCD                     = 0x01,
    PIT_COMMAND_MODE0                   = 0x00,
    PIT_COMMAND_MODE1                   = 0x02,
    PIT_COMMAND_MODE2                   = 0x04,
    PIT_COMMAND_MODE3                   = 0x06,
    PIT_COMMAND_MODE4                   = 0x08,
    PIT_COMMAND_MODE5                   = 0x0A,
    PIT_COMMAND_LATCH                   = 0x00,
    PIT_COMMAND_LOW                     = 0x10,
    PIT_COMMAND_HIGH                    = 0x20,
    PIT_COMMAND_BOTH                    = 0x30,
    PIT_COMMAND_COUNTER0                = 0x00,
    PIT_COMMAND_COUNTER1                = 0x40,
    PIT_COMMAND_COUNTER2                = 0x80,
    PIT_COMMAND_READBACK                = 0xC0

};

static struct base_driver driver;
static struct base_timer_interface itimer;
static struct rendezvous rduration;
static unsigned int duration;
static unsigned short divisor;

static void add_duration(struct base_device *device, unsigned int duration)
{

    rendezvous_lock(&rduration);
    rendezvous_sleep(&rduration, 1);

    duration = itimer.jiffies;

}

static void handle_irq(unsigned int irq, struct base_device *device)
{

    itimer.jiffies += 1;

    rendezvous_unsleep(&rduration, duration + 5000 < itimer.jiffies);

    if (duration + 5000 < itimer.jiffies)
        rendezvous_unlock(&rduration);

}

static void attach(struct base_device *device)
{

    unsigned short irq = device->bus->device_irq(device->bus, device);
    unsigned short io = platform_bus_get_base(device->bus, device->type);

    divisor = PIT_FREQUENCY / PIT_HERTZ;

    base_timer_init_interface(&itimer, add_duration);
    base_timer_register_interface(&itimer, device);
    pic_set_routine(irq, device, handle_irq);
    io_outb(io + PIT_REGISTER_COMMAND, PIT_COMMAND_COUNTER0 | PIT_COMMAND_BOTH | PIT_COMMAND_MODE3 | PIT_COMMAND_BINARY);
    io_outb(io + PIT_REGISTER_COUNTER0, divisor >> 0);
    io_outb(io + PIT_REGISTER_COUNTER0, divisor >> 8);

}

static void detach(struct base_device *device)
{

    unsigned short irq = device->bus->device_irq(device->bus, device);

    base_timer_unregister_interface(&itimer);
    pic_unset_routine(irq, device);

}

static unsigned int check(struct base_device *device)
{

    return device->type == PLATFORM_PIT_DEVICE_TYPE;

}

void init()
{

    base_init_driver(&driver, "pit", check, attach, detach);
    base_register_driver(&driver);

}

void destroy()
{

    base_unregister_driver(&driver);

}

