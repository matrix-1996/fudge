BIN:=$(PACKAGES_PATH)/date/date
OBJ:=$(PACKAGES_PATH)/date/date.o

$(BIN): $(OBJ) $(USERLIBS)
	$(LD) $(LDFLAGS) -o $@ $^

PACKAGES+=$(BIN)
PACKAGES_OBJECTS+=$(OBJ)
