include ./toolchain.mk

ISO = BrewOS.iso

.PHONY: boot kernel lib

all: kernel

run: $(ISO)
	@$(QEMU) -localtime -m 256M -boot d -cdrom $<
#	-s -S
	@rm -fr trace*

iso: $(ISO)

$(ISO): kernel
	@cp -f kernel/kernel.bin iso/kernel/kernel.bin
	@$(GENISO) -R -b boot/grub/i386-pc/eltorito.img \
		-no-emul-boot -boot-info-table -quiet -o $@ iso

boot:
	@echo "Building boot..."
#	@$(MAKE) -C boot/ all

kernel: lib
	@echo "Building kernel..."
	@$(MAKE) -C kernel all

lib:
	@echo "Building lib..."
	@$(MAKE) -C lib all
	
clean: clean-boot clean-kernel clean-lib

clean-boot:
#	@$(MAKE) -C boot/ clean

clean-kernel:
	@$(MAKE) -C kernel clean

clean-lib:
	@$(MAKE) -C lib clean
