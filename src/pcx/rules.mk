BIN_PCXCMAP:=\
    $(DIR_SRC)/pcx/pcxcmap \

OBJ_PCXCMAP:=\
    $(DIR_SRC)/pcx/pcx.o \
    $(DIR_SRC)/pcx/pcxcmap.o \
    $(DIR_SRC)/lib/file.o \
    $(DIR_SRC)/lib/gfx.o \
    $(DIR_SRC)/abi/abi.a \
    $(DIR_SRC)/fudge/fudge.a \

$(BIN_PCXCMAP): $(OBJ_PCXCMAP)
	@echo LD $@ 
	@$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

BIN_PCXDATA:=\
    $(DIR_SRC)/pcx/pcxdata \

OBJ_PCXDATA:=\
    $(DIR_SRC)/pcx/pcx.o \
    $(DIR_SRC)/pcx/pcxdata.o \
    $(DIR_SRC)/lib/file.o \
    $(DIR_SRC)/lib/gfx.o \
    $(DIR_SRC)/abi/abi.a \
    $(DIR_SRC)/fudge/fudge.a \

$(BIN_PCXDATA): $(OBJ_PCXDATA)
	@echo LD $@ 
	@$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

BIN:=$(BIN) $(BIN_PCXCMAP) $(BIN_PCXDATA)
OBJ:=$(OBJ) $(OBJ_PCXCMAP) $(OBJ_PCXDATA)
