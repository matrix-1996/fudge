struct base_bus
{

    struct resource resource;
    unsigned int type;
    const char *name;
    void (*setup)();
    unsigned int (*next)(unsigned int id);

};

struct base_driver
{

    struct resource resource;
    const char *name;
    void (*init)();
    unsigned int (*match)(unsigned int id);
    void (*attach)(unsigned int id);
    void (*detach)(unsigned int id);

};

void base_registerbus(struct base_bus *bus);
void base_registerdriver(struct base_driver *driver, unsigned int type);
void base_unregisterbus(struct base_bus *bus);
void base_unregisterdriver(struct base_driver *driver, unsigned int type);
void base_initbus(struct base_bus *bus, unsigned int type, const char *name, void (*setup)(), unsigned int (*next)(unsigned int id));
void base_initdriver(struct base_driver *driver, const char *name, void (*init)(), unsigned int (*match)(unsigned int id), void (*attach)(unsigned int id), void (*detach)(unsigned int id));
