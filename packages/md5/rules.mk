BIN:=$(PACKAGES_PATH)/md5/md5
OBJ:=$(PACKAGES_PATH)/md5/md5.o

$(BIN): $(OBJ) $(USERLIBS)
	$(LD) $(LDFLAGS) -o $@ $^

PACKAGES+=$(BIN)
PACKAGES_OBJECTS+=$(OBJ)
