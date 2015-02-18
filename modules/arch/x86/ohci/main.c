#include <fudge.h>
#include <kernel.h>
#include <base/base.h>
#include <system/system.h>
#include <arch/x86/pci/pci.h>

enum ohci_register
{

    OHCI_REGISTER_REVISION              = 0x00,
    OHCI_REGISTER_CONTROL               = 0x04,
    OHCI_REGISTER_STATUS                = 0x08,
    OHCI_REGISTER_INTSTATUS             = 0x0C,
    OHCI_REGISTER_INTENABLE             = 0x10,
    OHCI_REGISTER_INTDISABLE            = 0x14,
    OHCI_REGISTER_HCCA                  = 0x18,
    OHCI_REGISTER_PERIODCURRENT         = 0x1C,
    OHCI_REGISTER_CONTROLHEAD           = 0x20,
    OHCI_REGISTER_CONTROLCURRENT        = 0x24,
    OHCI_REGISTER_BULKHEAD              = 0x28,
    OHCI_REGISTER_BULKCURRENT           = 0x2C,
    OHCI_REGISTER_DONEHEAD              = 0x30,
    OHCI_REGISTER_FMINTERVAL            = 0x34,
    OHCI_REGISTER_FMREMAINING           = 0x38,
    OHCI_REGISTER_FMNUMBER              = 0x3C,
    OHCI_REGISTER_PERIODICSTART         = 0x40,
    OHCI_REGISTER_THRESHOLD             = 0x44,
    OHCI_REGISTER_RHDESCRIPTORA         = 0x48,
    OHCI_REGISTER_RHDESCRIPTORB         = 0x4C,
    OHCI_REGISTER_RHSTATUS              = 0x50

};

static struct base_driver driver;

static void driver_init()
{

}

static unsigned int driver_match(unsigned int id)
{

    return pci_inb(id, PCI_CONFIG_CLASS) == PCI_CLASS_SERIAL && pci_inb(id, PCI_CONFIG_SUBCLASS) == PCI_CLASS_SERIAL_USB && pci_inb(id, PCI_CONFIG_INTERFACE) == 0x10;

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

    base_initdriver(&driver, "ohci", driver_init, driver_match, driver_attach, driver_detach);

}

void module_register()
{

    base_registerdriver(&driver, PCI_BUS_TYPE);

}

void module_unregister()
{

    base_unregisterdriver(&driver, PCI_BUS_TYPE);

}

