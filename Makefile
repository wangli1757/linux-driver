CURRENTDIR :=$(shell pwd)
LIBDIR :=$(addsuffix /lib,$(CURRENTDIR))
INCLUDES := -I$(LIBDIR)

CFLAGS := -Wall -g 

BINDIR :=$(CURRENTDIR)/bin

export INCLUDES CFLAGS BINDIR

EXCLUDEDIRS :=$(CURRENTDIR)/bin $(CURRENTDIR)/lib $(CURRENTDIR)/.git $(CURRENTDIR)


CURDIRS := $(shell find $(CURRENTDIR) -maxdepth 1 -type d)
SUBDIRS :=$(filter-out $(EXCLUDEDIRS),$(CURDIRS))

MAKEDIRS :=$(foreach dir,$(SUBDIRS),$(shell find $(dir) -maxdepth 10 -type d))

default:
	@for d in $(MAKEDIRS); do (cd $$d && $(MAKE)); done
	
install:
	@for d in $(MAKEDIRS); do (cd $$d && $(MAKE) install); done

clean:
	@for d in $(MAKEDIRS); do (cd $$d && $(MAKE) clean); done

p:
	@echo "MakeDirs:$(MAKEDIRS)"
cleanbin:
	-$(RM) -r $(BINDIR)/* 
	

.PHONY: default install clean p