M:=\
    $(DIR_SRC)/modules/arch/x86/msr/msr.ko \

O:=\
    $(DIR_SRC)/modules/arch/x86/msr/main.o \
    $(DIR_SRC)/modules/arch/x86/msr/msr.o \

L:=\
    $(DIR_LIB)/fudge/fudge.a \

include $(DIR_MK)/mod.mk
