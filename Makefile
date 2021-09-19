CC = gcc
CFLAGS = -Wall -Iinclude
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
PREFIX ?= /usr/local
BIN ?= vm

.PHONY: all clean install uninstall

ifdef DEBUG
	CFLAGS += -g -Wextra -Wpedantic
endif

all: $(BIN) vas

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

vas: assembler.c # vas = vm assembler
	$(CC) $(CFLAGS) $^ -o $@

install: all
	cp $(BIN) $(PREFIX)/bin
uninstall:
	rm -f $(PREFIX)/bin/$(BIN)

clean:
	rm -f $(OBJ) $(BIN) vas

