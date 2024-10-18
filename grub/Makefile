GRUB_CFG_LOCATION=$(OUT_DIR)/ethos/boot/grub

all: $(GRUB_CFG_LOCATION)/grub.cfg

$(GRUB_CFG_LOCATION)/grub.cfg: $(GRUB_CFG_DIR)/grub.cfg
	mkdir -p $(GRUB_CFG_LOCATION)/
	cp $< $@
