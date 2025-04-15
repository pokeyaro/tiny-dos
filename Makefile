# -----------------------------------------------
# Makefile for Tiny-DOS project
# -----------------------------------------------

.PHONY: all run clean prebuild release

# -----------------------------------------------
# Source and Build Configuration
# -----------------------------------------------

# Build output directory
BUILD          = build

# Source file paths
BOOTLOADER_SRC = boot/bootloader.asm
KERNEL_SRC     = kernel/kernel.asm

# Compiled binary outputs
BOOTLOADER_BIN = $(BUILD)/bootloader.bin
KERNEL_BIN     = $(BUILD)/kernel.bin

# Disk image settings (1.44MB floppy)
IMG            = $(BUILD)/tiny.img
IMG_SIZE       = 2880
IMG_BS         = 512

# Emulator configuration
BOCHS_CFG      = bochsrc.bxrc

# -----------------------------------------------
# Build Process
# -----------------------------------------------

# Default target: clean build and run
all: clean run

# Create floppy image with bootloader and kernel
$(IMG): $(BOOTLOADER_BIN) $(KERNEL_BIN)
	@echo "[+] Creating 1.44MB floppy image..."
	dd if=/dev/zero of=$(IMG) bs=$(IMG_BS) count=$(IMG_SIZE)                    # Create blank image
	@echo "[+] Writing bootloader to image..."
	dd if=$(BOOTLOADER_BIN) of=$(IMG) bs=$(IMG_BS) seek=0 count=1 conv=notrunc  # Write to sector 0
	@echo "[+] Writing kernel to image..."
	dd if=$(KERNEL_BIN) of=$(IMG) bs=$(IMG_BS) seek=1 count=20 conv=notrunc     # Write to sectors 1-20
	@echo "[+] Floppy image creation complete."

# Compile bootloader.asm (raw binary format)
$(BOOTLOADER_BIN): $(BOOTLOADER_SRC) | prebuild
	@echo "[+] Compiling bootloader..."
	nasm -f bin -o $(BOOTLOADER_BIN) $(BOOTLOADER_SRC)

# Compile kernel.asm (raw binary format)
$(KERNEL_BIN): $(KERNEL_SRC) | prebuild
	@echo "[+] Compiling kernel..."
	nasm -f bin -o $(KERNEL_BIN) $(KERNEL_SRC)

# -----------------------------------------------
# Utility Targets
# -----------------------------------------------

# Create build directory structure
prebuild:
	@echo "[+] Creating build directory..."
	mkdir -p $(BUILD)

# Run in Bochs emulator
run: $(IMG)
	@echo "[+] Running in Bochs emulator..."
	bochs -q -f $(BOCHS_CFG)

# Clean build artifacts
clean:
	@echo "[+] Cleaning build artifacts..."
	rm -rf $(BUILD)

# Create timestamped release copy
release: $(IMG)
	@echo "[+] Creating release copy..."
	@mkdir -p disk
	@timestamp=$$(date +%Y%m%d_%H%M%S); \
	cp $(IMG) disk/tiny_dos_$${timestamp}.img; \
	echo "[+] Copied tiny.img to disk/tiny_dos_$(TIMESTAMP).img"
	@echo "[+] Release copy created."
