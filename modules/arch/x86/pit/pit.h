#define PIT_FREQUENCY                   1193182
#define PIT_HERTZ                       100
#define PIT_IRQ                         0x00
#define PIT_DEVICE_TYPE                 0x2002

struct pit_device
{

    struct base_device base;
    unsigned short divisor;
    unsigned short jiffies;

};

struct pit_driver
{

    struct base_driver base;
    struct timer_interface itimer;

};

void pit_init_device(struct pit_device *device, unsigned int irq);
void pit_init_driver(struct pit_driver *driver);
