CC := gcc
LD := gcc
CFLAGS += -Iinclude -lpthread
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
BIN := vm
VERBOSE := 0

# verbosity for CC
REAL_CC := $(CC)
CC_0 = @echo "CC $<"; $(REAL_CC)
CC_1 = $(REAL_CC)
CC = $(CC_$(VERBOSE))

# verbosity for LD
REAL_LD := $(LD)
LD_0 = @echo "LD $^"; $(REAL_LD)
LD_1 = $(REAL_LD)
LD = $(LD_$(VERBOSE))

.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJ)
	$(LD) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BIN)
