CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Iinclude
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
BIN = as

ifdef DEBUG
	CFLAGS += -g
endif

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BIN)


.PHONY: clean all
