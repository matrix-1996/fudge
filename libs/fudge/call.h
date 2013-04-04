unsigned int call_bind(unsigned int index, unsigned int pindex, unsigned int cindex);
unsigned int call_close(unsigned int index);
unsigned int call_execute(unsigned int index);
unsigned int call_exit();
unsigned int call_open(unsigned int index, unsigned int pindex, unsigned int count, const char *path);
unsigned int call_load(unsigned int index);
unsigned int call_mount(unsigned int index, unsigned int pindex, unsigned int cindex);
unsigned int call_read(unsigned int index, unsigned int offset, unsigned int count, void *buffer);
unsigned int call_spawn(unsigned int index);
unsigned int call_unload(unsigned int index);
unsigned int call_write(unsigned int index, unsigned int offset, unsigned int count, void *buffer);
