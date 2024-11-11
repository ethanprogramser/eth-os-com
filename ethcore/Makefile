ETHCORE_BOOT_SRCS=$(wildcard $(ETHCORE_SRC_DIR)/boot/*.s)
ETHCORE_KERNEL_SRCS=$(wildcard $(ETHCORE_SRC_DIR)/kernel/*.c)
ETHCORE_KLIB_SRCS=$(wildcard $(ETHCORE_SRC_DIR)/klib/*.c)
ETHCORE_BOOT_OBJS=$(patsubst $(ETHCORE_SRC_DIR)/boot/%.s, $(OBJ_DIR)/ethcore/boot/%.o, $(ETHCORE_BOOT_SRCS))
ETHCORE_KERNEL_OBJS=$(patsubst $(ETHCORE_SRC_DIR)/kernel/%.c, $(OBJ_DIR)/ethcore/kernel/%.o, $(ETHCORE_KERNEL_SRCS))
ETHCORE_KLIB_OBJS=$(patsubst $(ETHCORE_SRC_DIR)/klib/%.c, $(OBJ_DIR)/ethcore/klib/%.o, $(ETHCORE_KLIB_SRCS))

KERNEL_NAME=ethcore

include ethcore.mk

all: $(OBJ_DIR)/ethcore boot kernel klib link place

$(OBJ_DIR)/ethcore:
	mkdir -p $@/
	mkdir -p $@/boot/
	mkdir -p $@/kernel/
	mkdir -p $@/klib/

boot: $(ETHCORE_BOOT_OBJS)

$(OBJ_DIR)/ethcore/boot/%.o: $(ETHCORE_SRC_DIR)/boot/%.s
	$(EECHO) "[$(BLUE)ETHCORE$(NORMAL)] Compiling boot object \"$<\"..."
	$(ASM) $(ASMFLAGS) -o $@ $<

kernel: $(ETHCORE_KERNEL_OBJS)

$(OBJ_DIR)/ethcore/kernel/%.o: $(ETHCORE_SRC_DIR)/kernel/%.c
	$(EECHO) "[$(BLUE)ETHCORE$(NORMAL)] Compiling kernel object \"$<\"..."
	$(CC) $(CFLAGS) -c -I./ -o $@ $<

klib: $(ETHCORE_KLIB_OBJS)

$(OBJ_DIR)/ethcore/klib/%.o: $(ETHCORE_SRC_DIR)/klib/%.c
	$(EECHO) "[$(BLUE)ETHCORE$(NORMAL)] Compiling KLib object \"$<\"..."
	$(CC) $(CFLAGS) -c -I./ -o $@ $<

link: boot kernel klib
	$(EECHO) "[$(BLUE)ETHCORE$(NORMAL)] Linking..."
	$(LD) $(LDFLAGS) -T $(ETHCORE_SRC_DIR)/linker.ld -o \
		$(BUILD_DIR)/$(KERNEL_NAME) \
		$(ETHCORE_BOOT_OBJS) $(ETHCORE_KERNEL_OBJS) $(ETHCORE_KLIB_OBJS)

place: link
	mkdir -p $(OUT_DIR)/ethos/boot/
	cp $(BUILD_DIR)/$(KERNEL_NAME) $(OUT_DIR)/ethos/boot/$(KERNEL_NAME)
