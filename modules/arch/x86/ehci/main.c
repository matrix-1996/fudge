#include <fudge.h>
#include <kernel.h>
#include <base/base.h>
#include <arch/x86/pci/pci.h>

enum ehci_register
{

    EHCI_REGISTER_COMMAND               = 0x00,
    EHCI_REGISTER_STATUS                = 0x04,
    EHCI_REGISTER_INTERRUPT             = 0x08,
    EHCI_REGISTER_FRAMEINDEX            = 0x0C,
    EHCI_REGISTER_SEGMENT               = 0x10,
    EHCI_REGISTER_LISTBASE              = 0x14,
    EHCI_REGISTER_LISTNEXT              = 0x18,
    EHCI_REGISTER_FLAG                  = 0x40

};

static struct base_driver driver;

static void driver_init()
{

}

static unsigned int driver_match(unsigned int type, unsigned int id)
{

    if (type != PCI_BUS_TYPE)
        return 0;

    return pci_inb(id, PCI_CONFIG_CLASS) == PCI_CLASS_SERIAL && pci_inb(id, PCI_CONFIG_SUBCLASS) == PCI_CLASS_SERIAL_USB && pci_inb(id, PCI_CONFIG_INTERFACE) == 0x20;

}

static void driver_attach(unsigned int id)
{

    /*
    unsigned int bar0 = pci_ind(id, PCI_CONFIG_BAR0);
    */

}

static void driver_detach(unsigned int id)
{

}

void module_init()
{

    base_initdriver(&driver, "ehci", driver_init, driver_match, driver_attach, driver_detach);

}

void module_register()
{

    base_registerdriver(&driver);

}

void module_unregister()
{

    base_unregisterdriver(&driver);

}

