M:=\
    $(DIR_SRC)/modules/arch/x86/cirrus/cirrus.ko \

O:=\
    $(DIR_SRC)/modules/arch/x86/cirrus/main.o \

L:=\
    $(DIR_LIB)/fudge/fudge.a \

include $(DIR_MK)/mod.mk
