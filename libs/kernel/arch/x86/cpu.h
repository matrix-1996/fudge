unsigned int cpu_get_cr0();
unsigned int cpu_get_cr2();
unsigned int cpu_get_cr3();
unsigned int cpu_get_cr4();
unsigned int cpu_get_eflags();
void cpu_halt();
void cpu_set_cr0(unsigned int value);
void cpu_set_cr2(unsigned int value);
void cpu_set_cr3(unsigned int value);
void cpu_set_cr4(unsigned int value);
void cpu_set_gdt(void *pointer);
void cpu_set_idt(void *pointer);
void cpu_set_eflags(unsigned int value);
void cpu_set_tss(unsigned int value);