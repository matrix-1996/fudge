#include "../memory.h"
#include "elf.h"

unsigned int elf_validate(struct elf_header *header)
{

    char id[] = {ELF_IDENTITY_MAGIC0, ELF_IDENTITY_MAGIC1, ELF_IDENTITY_MAGIC2, ELF_IDENTITY_MAGIC3};

    return memory_match(header->identify, id, 4);

}

unsigned int elf_find_symbol(struct elf_header *header, struct elf_section_header *sectionTable, struct elf_section_header *symbolHeader, struct elf_symbol *symbolTable, char *stringTable, unsigned int count, char *symbol)
{

    unsigned int i;

    for (i = 0; i < symbolHeader->size / symbolHeader->esize; i++)
    {

        if (memory_match(symbol, stringTable + symbolTable[i].name, count))
            return (header->type == ELF_TYPE_RELOCATABLE) ? sectionTable[symbolTable[i].shindex].address + sectionTable[symbolTable[i].shindex].offset + symbolTable[i].value : symbolTable[i].value;

    }

    return 0;

}

void elf_relocate_symbol(unsigned int address, unsigned int type, unsigned int addend)
{

    unsigned int *entry = (unsigned int *)(address);

    switch (type)
    {

        case ELF_RELOC_TYPE_32:

            *entry += addend;

            break;

        case ELF_RELOC_TYPE_PC32:

            *entry += addend - address;

            break;

    }

}

void elf_relocate_section(struct elf_section_header *sectionTable, struct elf_section_header *relocationHeader, struct elf_section_header *relocationData, struct elf_relocation *relocationTable, struct elf_symbol *symbolTable, unsigned int address)
{

    unsigned int i;

    for (i = 0; i < relocationHeader->size / relocationHeader->esize; i++)
    {

        unsigned char type = relocationTable[i].info & 0x0F;
        unsigned char index = relocationTable[i].info >> 8;
        unsigned int offset = relocationData->offset + relocationTable[i].offset;
        unsigned int addend = sectionTable[symbolTable[index].shindex].offset + symbolTable[index].value;

        if (symbolTable[index].shindex)
            elf_relocate_symbol(address + offset, type, address + addend);
        else
            elf_relocate_symbol(address + offset, type, 0);

    }

}
