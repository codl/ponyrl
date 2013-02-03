CC=gcc
WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
-Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
-Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
-Wuninitialized -Wconversion -Wstrict-prototypes
CFLAGS=-lm -std=gnu99 $(WARNINGS)
PROJDIRS := src
SRCFILES := $(shell find $(PROJDIRS) -type f -name "*.c")
HDRFILES := $(shell find $(PROJDIRS) -type f -name "*.h")
OBJFILES := $(patsubst %.c,%.o,$(SRCFILES))
DEPFILES := $(patsubst %.c,%.d,$(SRCFILES))

.PHONY: all clean

all: test

clean:
	@-$(RM) $(wildcard $(OBJFILES) $(DEPFILES) test)

%.o: %.c Makefile
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEPFILES)

test: $(OBJFILES)
	@$(CC) $(CFLAGS) $^ -o $@
