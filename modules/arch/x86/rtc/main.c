#include <base/base.h>
#include "rtc.h"

static struct rtc_device device;

void init()
{

    rtc_init_device(&device, RTC_IRQ);
    base_register_device(&device.base);

}

void destroy()
{

    base_unregister_device(&device.base);

}
