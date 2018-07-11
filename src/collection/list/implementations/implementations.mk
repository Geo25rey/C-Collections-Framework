ifeq ($(BASE_DIR),)
abort:   ## This MUST be the first target :( ugly
	@echo Make must be run from the root of the project && false
endif

export IMPLEMENTATIONS_OBJ:= implementations/arraylist.o

all: $(IMPLEMENTATIONS_OBJ:implementations=)

arraylist.o: ../list.h arraylist.c
        gcc -c -Wall -fpic arraylist.c
