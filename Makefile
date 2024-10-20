ISO_NAME=ethos.iso

include config.mk

.PHONY: all dirs ethcore grub iso run clean

all: dirs ethcore grub iso

# Create directories
dirs:
	mkdir -p $(BUILD_DIR)/
	mkdir -p $(OBJ_DIR)/
	mkdir -p $(OUT_DIR)/ethos/

# Eth-Core
ethcore:
	@echo "Compiling Eth-Core..."
	$(MAKE) -C $(ETHCORE_SRC_DIR)

# Place default GRUB config
grub: ethcore
	@echo "Placing default GRUB config..."
	$(MAKE) -C $(abspath grub)

# Make an `.iso` file
iso: ethcore grub
	@echo "Making an iso..."
	mkdir -p $(OUT_DIR)/iso/
	grub-mkrescue -o $(OUT_DIR)/iso/$(ISO_NAME) $(OUT_DIR)/ethos

# Run
run: all
	qemu-system-i386 -drive format=raw,file=$(OUT_DIR)/iso/$(ISO_NAME)

# Clean-up everything
clean:
	rm -rf $(BUILD_DIR)/*
	rm -rf $(OBJ_DIR)/*
	rm -rf $(OUT_DIR)/*
