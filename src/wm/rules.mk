BIN_WDRAW:=\
    $(DIR_SRC)/wm/wdraw \

OBJ_WDRAW:=\
    $(DIR_SRC)/wm/wdraw.o \
    $(DIR_SRC)/wm/box.o \
    $(DIR_SRC)/wm/element.o \
    $(DIR_SRC)/lib/file.o \
    $(DIR_SRC)/format/pcf.o \
    $(DIR_SRC)/fudge/fudge.a \
    $(DIR_SRC)/abi/abi.a \

$(BIN_WDRAW): $(OBJ_WDRAW)
	@echo LD $@ 
	@$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

BIN_WEDIT:=\
    $(DIR_SRC)/wm/wedit \

OBJ_WEDIT:=\
    $(DIR_SRC)/wm/wedit.o \
    $(DIR_SRC)/wm/box.o \
    $(DIR_SRC)/wm/element.o \
    $(DIR_SRC)/wm/send.o \
    $(DIR_SRC)/lib/file.o \
    $(DIR_SRC)/fudge/fudge.a \
    $(DIR_SRC)/abi/abi.a \

$(BIN_WEDIT): $(OBJ_WEDIT)
	@echo LD $@ 
	@$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

BIN_WM:=\
    $(DIR_SRC)/wm/wm \

OBJ_WM:=\
    $(DIR_SRC)/wm/wm.o \
    $(DIR_SRC)/wm/box.o \
    $(DIR_SRC)/wm/element.o \
    $(DIR_SRC)/wm/send.o \
    $(DIR_SRC)/lib/file.o \
    $(DIR_SRC)/fudge/fudge.a \
    $(DIR_SRC)/abi/abi.a \

$(BIN_WM): $(OBJ_WM)
	@echo LD $@ 
	@$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

BIN_WSHELL:=\
    $(DIR_SRC)/wm/wshell \

OBJ_WSHELL:=\
    $(DIR_SRC)/wm/wshell.o \
    $(DIR_SRC)/wm/box.o \
    $(DIR_SRC)/wm/element.o \
    $(DIR_SRC)/wm/send.o \
    $(DIR_SRC)/wm/keymap.o \
    $(DIR_SRC)/lib/file.o \
    $(DIR_SRC)/fudge/fudge.a \
    $(DIR_SRC)/abi/abi.a \

$(BIN_WSHELL): $(OBJ_WSHELL)
	@echo LD $@ 
	@$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

BIN_WTEXT:=\
    $(DIR_SRC)/wm/wtext \

OBJ_WTEXT:=\
    $(DIR_SRC)/wm/wtext.o \
    $(DIR_SRC)/wm/box.o \
    $(DIR_SRC)/wm/element.o \
    $(DIR_SRC)/lib/file.o \
    $(DIR_SRC)/fudge/fudge.a \
    $(DIR_SRC)/abi/abi.a \

$(BIN_WTEXT): $(OBJ_WTEXT)
	@echo LD $@ 
	@$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

BIN:=$(BIN) $(BIN_WDRAW) $(BIN_WEDIT) $(BIN_WM) $(BIN_WSHELL) $(BIN_WTEXT)
OBJ:=$(OBJ) $(OBJ_WDRAW) $(OBJ_WEDIT) $(OBJ_WM) $(OBJ_WSHELL) $(OBJ_WTEXT)
