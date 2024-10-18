# Makefile
CC=i386-elf-gcc
LD=i386-elf-ld
AS=i386-elf-as

CFLAGS=-ffreestanding -O2 -nostdlib -lgcc
LDFLAGS=-T linker.ld

BUILD_DIR=build



SOURCE_FILES=boot kernel

SOURCE_DIR=src

OBJDIR=$(BUILD_DIR)/obj

OBJ_FILES=$(addprefix $(OBJDIR)/, \
		boot.o \
		kernel.o \
		)

KERNEL_BIN=$(BUILD_DIR)/kernel.bin


all: $(KERNEL_BIN)

$(KERNEL_BIN): $(OBJ_FILES)
	$(LD) $(LDFLAGS) -o $(KERNEL_BIN) $(OBJ_FILES)

$(OBJDIR)/boot.o: $(SOURCE_DIR)/boot.s
	mkdir -p $(OBJDIR)
	$(AS) $(SOURCE_DIR)/boot.s -o $(OBJDIR)/boot.o

$(OBJDIR)/kernel.o: $(SOURCE_DIR)/kernel.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $(SOURCE_DIR)/kernel.c -o $(OBJDIR)/kernel.o

clean:
	rm -rf $(OBJDIR) kernel.bin

run: all
	qemu-system-i386 -kernel $(KERNEL_BIN)

