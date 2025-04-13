# -----------------------------------------------
# Makefile for Tiny-DOS project
# -----------------------------------------------

.PHONY: all run clean prebuild

# File paths and configurations
BOOTLOADER_SRC = boot/bootloader.asm
BOOTLOADER_BIN = build/bootloader.bin
IMG = build/tiny.img
BOCHS_CFG = bochsrc.bxrc
IMG_SIZE = 2880
IMG_BS = 512

# Default target: clean build and run
all: clean run

# Compile bootloader.asm to raw binary
$(BOOTLOADER_BIN): $(BOOTLOADER_SRC) | prebuild
	nasm -f bin -Wall -o $(BOOTLOADER_BIN) $(BOOTLOADER_SRC)

# Create floppy image and write bootloader
$(IMG): $(BOOTLOADER_BIN) $(KERNEL_BIN)
	# Create blank 1.44MB floppy image
	dd if=/dev/zero of=$(IMG) bs=$(IMG_BS) count=$(IMG_SIZE)
	# Write bootloader to first sector
	dd if=$(BOOTLOADER_BIN) of=$(IMG) bs=$(IMG_BS) count=1 conv=notrunc

# Create build directory if not exists
prebuild:
	mkdir -p build

# Run Bochs emulator with configuration file
run: $(IMG)
	bochs -q -f $(BOCHS_CFG)

# Clean build artifacts
clean:
	rm -rf build
