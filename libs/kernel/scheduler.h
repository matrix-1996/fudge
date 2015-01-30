struct task *scheduler_findactive();
struct task *scheduler_findinactive();
void scheduler_mailboxes_addactive(struct list *mailboxes);
void scheduler_mailboxes_removeactive(struct list *mailboxes);
void scheduler_mailboxes_removeall(struct list *mailboxes);
unsigned int scheduler_mailboxes_readactive(struct list *mailboxes, unsigned int count, void *buffer);
unsigned int scheduler_mailboxes_send(struct list *mailboxes, unsigned int count, void *buffer);
void scheduler_use(struct task *task);
void scheduler_unuse(struct task *task);
void scheduler_register_task(struct task *task);
void scheduler_unregister_task(struct task *task);
void scheduler_setup();
