.PHONY: all clean

PROJECT := \
	hello \
	strsplit

all: $(PROJECT)

clean:
	rm -rf *.o $(PROJECT)

ifeq ($(V),1)
MSG_C=
MSG_L=
PREFIX=
else
MSG_C=@echo "[C] $@ ..."
MSG_L=@echo "[L] $@ ..."
PREFIX=@
endif

CC := gcc

GLIB_CFLAGS := $(shell pkg-config --cflags glib-2.0)
GLIB_LDFLAGS := $(shell pkg-config --libs glib-2.0)

CFLAGS := -Wall
CFLAGS += $(GLIB_CFLAGS)

LDLAGS :=
LDLAGS += $(GLIB_LDFLAGS)

%.o: %.c
	$(MSG_C)
	$(PREFIX)$(CC) -c -o $@ $(CFLAGS) $<

strsplit: strsplit.o
	$(MSG_L)
	$(PREFIX)$(CC) -o $@ -g $^ $(LDLAGS)

hello: hello.o
	$(MSG_L)
	$(PREFIX)$(CC) -o $@ -g $^ $(LDLAGS)
