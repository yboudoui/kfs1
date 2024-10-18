NAME=dyan_os
# Makefile
CC=i386-elf-gcc
LD=i386-elf-ld
AS=i386-elf-as

CFLAGS=-ffreestanding -O2 -nostdlib -lgcc
LDFLAGS=-T linker.ld

BUILD_DIR=build
OBJECT_DIR=$(BUILD_DIR)/obj

SOURCE_DIR=code/src
INCLUDE_DIR=code/inc

SRCS= $(addprefix $(SOURCE_DIR)/, \
	keyboard/keyboard.c \
	terminal/terminal.c \
	utils/strlen.c \
	utils/itoa_base.c \
	vga/vga.c \
	kernel.c \
)

INCS = $(addprefix $(INCLUDE_DIR)/, \
	keyboard \
	terminal \
	utils \
	vga \
)

OBJS = $(patsubst $(SOURCE_DIR)/%.c, $(OBJECT_DIR)/%.o, $(SRCS)) $(OBJECT_DIR)/boot.o

KERNEL_BIN=$(BUILD_DIR)/$(NAME).bin


all: $(KERNEL_BIN)

$(KERNEL_BIN): $(OBJS)
	$(LD) $(LDFLAGS) -o $(KERNEL_BIN) $(OBJS)

$(OBJECT_DIR)/boot.o: $(SOURCE_DIR)/boot.s
	mkdir -p $(OBJECT_DIR)
	$(AS) $(SOURCE_DIR)/boot.s -o $(OBJECT_DIR)/boot.o


$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(addprefix -I , $(INCS)) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

re: clean all

iso: all
	@mkdir -p $(BUILD_DIR)/isodir/boot/grub
	@cp $(BUILD_DIR)/$(NAME).bin $(BUILD_DIR)/isodir/boot/$(NAME).bin
	@cp code/grub.cfg $(BUILD_DIR)/isodir/boot/grub/grub.cfg
	@grub-mkrescue -o $(BUILD_DIR)/$(NAME).iso $(BUILD_DIR)/isodir

run: all
	qemu-system-i386 -kernel $(KERNEL_BIN)

runiso: iso
	qemu-system-i386 -cdrom $(BUILD_DIR)/$(NAME).iso

