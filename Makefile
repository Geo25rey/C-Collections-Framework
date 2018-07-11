ifeq ($(BUILD_DIR),)
abort:   ## This MUST be the first target :( ugly
	@echo Variable BUILD_DIR not set as command line arguement && false
else
ifeq (,$(wildcard $(BUILD_DIR)))
$(shell mkdir $(BUILD_DIR)) # Creates build directory if it doesn't exist
endif
endif

SHELL := /bin/bash
BASE_DIR:=$(shell pwd)
CURRENT_DIR:=.

export

all: 
	$(MAKE) -C $(CURRENT_DIR)/src -f src.mk

temp: list.o
	gcc -shared -o libcollection.so list.o

list.o: list.h list.c
	gcc -c -Wall -fpic list.c

clean: 
	rm -fR *.o

superClean: clean
	rm -f *.so

