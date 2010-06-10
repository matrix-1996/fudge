#ifndef MEMORY_H
#define MEMORY_H

extern void *memory_copy(void *dest, const void *src, int32_t count);
extern void *memory_set(void *dest, int8_t val, int32_t count);
extern uint16_t *memory_setw(uint16_t *dest, uint16_t val, int32_t count);

#endif

