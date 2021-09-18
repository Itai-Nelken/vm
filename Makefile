CC = gcc
CFLAGS = -Wall -Iinclude
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
BIN ?= vm

ifdef DEBUG
	CFLAGS += -g -Wextra -Wpedantic
endif

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ) $(BIN)

