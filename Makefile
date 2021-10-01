CC := gcc
BUILD_DIR := build
OS := $(shell uname -s)
ARCH := $(shell uname -m)

all: vm vas

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

vm: $(BUILD_DIR)
	$(MAKE) -C VM
	@cp VM/vm $(BUILD_DIR)/vm

vas: $(BUILD_DIR)
	$(MAKE) -C assembler
	@cp assembler/vas $(BUILD_DIR)/vas

clean:
	$(MAKE) clean -C VM
	$(MAKE) clean -C assembler
	rm -rf $(BUILD_DIR)

release: vm vas
	tar -cvf VM_$(shell date +"%d-%m-%Y")_$(OS)-$(ARCH).tar.xz build/ examples/ syntax/ README.md CHANGELOG.md

.PHONY: all clean release
