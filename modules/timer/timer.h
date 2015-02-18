struct timer_interface
{

    struct system_interface base;
    struct system_node sleep;

};

void timer_notify(struct timer_interface *interface, unsigned int count, void *buffer);
void timer_registerinterface(struct timer_interface *interface, unsigned int id);
void timer_unregisterinterface(struct timer_interface *interface);
void timer_initinterface(struct timer_interface *interface, struct base_driver *driver);
