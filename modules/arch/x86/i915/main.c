#include <fudge/module.h>
#include <system/system.h>
#include <base/base.h>
#include <video/video.h>
#include "i915.h"

static struct i915_driver driver;

void init()
{

    i915_init_driver(&driver);
    base_register_driver(&driver.base);

}

void destroy()
{

    base_unregister_driver(&driver.base);

}

