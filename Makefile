CC := gcc
BUILD_DIR := build
OS := $(shell uname -s)
ARCH := $(shell uname -m)
CFLAGS := -Wall -Wextra -Wpedantic -Iinclude
DEBUG := 0
VERBOSE := 0

ifneq ($(DEBUG), 0)
	CFLAGS += -g
endif

all: vm vas

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

vm: $(BUILD_DIR)
	$(MAKE) CFLAGS="$(CFLAGS)" VERBOSE=$(VERBOSE) -C VM
	@cp VM/vm $(BUILD_DIR)/vm

vas: $(BUILD_DIR)
	$(MAKE) CFLAGS="$(CFLAGS)" VERBOSE=$(VERBOSE) -C assembler
	@cp assembler/vas $(BUILD_DIR)/vas

clean:
	$(MAKE) clean -C VM
	$(MAKE) clean -C assembler
	rm -rf $(BUILD_DIR)

release: vm vas
	tar -cvf VM_$(shell date +"%d-%m-%Y")_$(OS)-$(ARCH).tar.xz build/ examples/ syntax/ README.md CHANGELOG.md

.PHONY: all clean release
