#ifndef INITRD_H
#define INITRD_H

typedef struct initrd_header
{

    unsigned int nfiles;

} initrd_header_t;

typedef struct initrd_file_header
{

    unsigned char magic;
    char name[64];
    unsigned int offset;
    unsigned int length;

} initrd_file_header_t;

extern vfs_node_t *initrd_init(unsigned int location);

#endif

