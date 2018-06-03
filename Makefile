#Makefile for STM8s TM1637 demo
#Author: indigo6alpha
#Copyright 2018
#LICENSE: GPL

# We're assuming POSIX conformance
.POSIX:

#Compiler
CC = sdcc

#Platform
PLATFORM = stm8

#Product name
PNAME = main

#Folders **** MAKE SURE TO CHANGE ACCORDING TO YOUR STRUCTURE!!! ****
#Output directory for intermediate and final compiled file(s)
ODIR = bin
#Directory for helpers
IDIR = inc
SDIR = src
DIST = dist

# In case you ever want a different name for the main source file
MAINSRC = $(PNAME).c

# These are the sources that must be compiled to .rel files:
EXTRASRCS = \
	$(SDIR)/gpio.c\
	$(SDIR)/clock.c\
	$(SDIR)/tm1637.c

# The list of .rel files can be derived from the list of their source files
RELS = $(EXTRASRCS:.c=.rel)

INCLUDES = -I$(IDIR)
CFLAGS   = -m$(PLATFORM)
LIBS     = -l$(PLATFORM)

# This just provides the conventional target name "all"; it is optional
# Note: I assume you set PNAME via some means not exhibited in your original file
all: $(PNAME)

# How to build the overall program
$(PNAME): $(MAINSRC) $(RELS)
	@mkdir -p $(ODIR) $(DIST)
	$(CC) $(INCLUDES) $(CFLAGS) $(LIBS) $(MAINSRC) $(wildcard $(ODIR)/*.rel) -o$(ODIR)/ && cp $(ODIR)/$(PNAME).ihx $(DIST)

# How to build any .rel file from its corresponding .c file
# GNU would have you use a pattern rule for this, but that's GNU-specific
.c.rel:
	@mkdir -p $(ODIR)
	$(CC) -c $(INCLUDES) $(CFLAGS) $(LIBS) $< -o$(ODIR)/

# Suffixes appearing in suffix rules we care about.
# Necessary because .rel is not one of the standard suffixes.
.SUFFIXES: .c .rel


#phonies
.PHONY:	clean flash sudoflash

clean:
	@echo "Removing $(ODIR) and $(DIST)..."
	@rm -rf $(ODIR) $(DIST)
	@echo "Done."

flash:
	stm8flash -cstlinkv2 -pstm8s103f3 -w$(DIST)/$(PNAME).ihx

sudoflash:
	sudo stm8flash -cstlinkv2 -pstm8s103f3 -w$(DIST)/$(PNAME).ihx
