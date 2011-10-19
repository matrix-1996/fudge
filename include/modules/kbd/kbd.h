#ifndef MODULES_KBD_H
#define MODULES_KBD_H

#define KBD_PORT_READ 0x60
#define KBD_BUFFER_SIZE 256

struct kbd_device
{

    struct modules_device base;
    char buffer[KBD_BUFFER_SIZE];
    unsigned int bufferSize;
    unsigned int bufferHead;
    unsigned int bufferTail;
    unsigned int escaped;
    unsigned int toggleAlt;
    unsigned int toggleCtrl;
    unsigned int toggleShift;
    unsigned int (*getc)(struct kbd_device *device, char *buffer);
    unsigned int (*putc)(struct kbd_device *device, char *buffer);

};

extern void kbd_init();

#endif

