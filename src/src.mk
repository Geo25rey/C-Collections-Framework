ifeq ($(BASE_DIR),)
abort:   ## This MUST be the first target :( ugly
	@echo Make must be run from the root of the project && false
endif

CURRENT_DIR:=$(CURRENT_DIR)/src

all: collection

collection: collection/*
	$(MAKE) -C $(BASE_DIR)/$(CURRENT_DIR)/collection -f collection.mk
