CC = gcc
CFLAGS = -Wall -Iinclude
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
PREFIX ?= /usr/local
BIN ?= vm

ifdef DEBUG
	CFLAGS += -g -Wextra -Wpedantic
endif

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

install: all
	cp $(BIN) $(PREFIX)/bin
uninstall:
	rm -f $(PREFIX)/bin/$(BIN)

clean:
	rm -f $(OBJ) $(BIN)

