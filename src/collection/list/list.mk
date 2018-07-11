ifeq ($(BASE_DIR),)
abort:   ## This MUST be the first target :( ugly
	@echo Make must be run from the root of the project && false
endif

CURRENT_DIR+=/list

all: implementations liblist.so

implementations: implementations/* export CURRENT_DIR+=/implementations
	$(MAKE) -C $(BASE_DIR)/$(CURRENT_DIR) -f implementations.mk

liblist.so: implementations list.o
        gcc -shared -o liblist.so list.o $(IMPLEMENTATIONS_OBJ)

list.o: list.h list.c
        gcc -c -Wall -fpic list.c
