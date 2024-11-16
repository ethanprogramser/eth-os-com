ISO_NAME=ethos.iso

include config.mk
include misc.mk

.PHONY: actions all dirs ethcore grub iso run clean oldiso

all: dirs ethcore grub fastiso
release: dirs ethcore grub iso

# Create directories
dirs:
	mkdir -p $(BUILD_DIR)/
	mkdir -p $(OBJ_DIR)/
	mkdir -p $(OUT_DIR)/ethos/

# Eth-Core
ethcore:
	$(EECHO) "[$(BLUE)ETHCORE$(NORMAL)] Compiling Eth-Core..."
	$(MAKE) -C $(ETHCORE_SRC_DIR)

# Place default GRUB config
grub: ethcore
	$(EECHO) "[$(BLUE)GRUB$(NORMAL)] Placing default GRUB config..."
	$(MAKE) -C $(abspath grub)

# Make an `.iso` file
iso: ethcore grub $(OUT_DIR)/iso/$(ISO_NAME)

$(OUT_DIR)/iso/$(ISO_NAME):
	$(EECHO) "[$(GREEN)ISO$(NORMAL)] Making release ISO..."
	mkdir -p $(OUT_DIR)/iso
	dd if=/dev/zero of=$(OUT_DIR)/iso/$(ISO_NAME) bs=1M count=100
	mkfs.fat -F32 $(OUT_DIR)/iso/$(ISO_NAME)
	sudo losetup /dev/loop0 $(OUT_DIR)/iso/$(ISO_NAME)
	sudo mkdir $(OUT_DIR)/iso/tmp
	sudo mount /dev/loop0 $(OUT_DIR)/iso/tmp
	sudo mkdir $(OUT_DIR)/iso/tmp/boot
	sudo grub-install --force --target=i386-pc --boot-directory=$(OUT_DIR)/iso/tmp/boot /dev/loop0
	sudo cp -r $(OUT_DIR)/ethos/* $(OUT_DIR)/iso/tmp
	sudo umount $(OUT_DIR)/iso/tmp
	sudo losetup -d /dev/loop0
	sudo rm -rf $(OUT_DIR)/iso/tmp

fastiso: ethcore grub
	$(EECHO) "[$(GREEN)ISO$(NORMAL)] Making fast ISO..."
	mkdir -p $(OUT_DIR)/iso
	grub-mkrescue -o $(OUT_DIR)/iso/$(ISO_NAME) $(OUT_DIR)/ethos

# Run
run: all
	$(EECHO) "[$(RED)QEMU$(NORMAL)] Running ISO..."
	qemu-system-i386 -drive format=raw,file=$(OUT_DIR)/iso/$(ISO_NAME)

# Run with KVM support
run-kvm: all
	$(EECHO) "[$(RED)QEMU$(NORMAL)] Running ISO with KVM support..."
	qemu-system-i386 --enable-kvm -drive format=raw,file=$(OUT_DIR)/iso/$(ISO_NAME)

# Clean-up everything
clean:
	rm -rf $(BUILD_DIR)/*
	rm -rf $(OBJ_DIR)/*
	rm -rf $(OUT_DIR)/*
