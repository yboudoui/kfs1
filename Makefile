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

SRCS= $(addprefix $(SOURCE_DIR)/ , \
	terminal/terminal.c \
	utils/strlen.c \
	vga/vga.c \
	kernel.c \
)

INCS = $(addprefix $(INCLUDE_DIR)/ , \
	terminal \
	utils \
	vga \
)

OBJS = $(patsubst $(SOURCE_DIR)/%.c, $(OBJECT_DIR)/%.o, $(SRCS))

# OBJ_FILES=$(addprefix $(OBJDIR)/, \
# 		boot.o \
# 		kernel.o \
# 		)

KERNEL_BIN=$(BUILD_DIR)/kernel.bin


all: $(KERNEL_BIN)

$(KERNEL_BIN): $(OBJS)
	$(LD) $(LDFLAGS) -o $(KERNEL_BIN) $(OBJS)

$(OBJECT_DIR)/boot.o: $(SOURCE_DIR)/boot.s
	mkdir -p $(OBJECT_DIR)
	$(AS) $(SOURCE_DIR)/boot.s -o $(OBJECT_DIR)/boot.o

$(OBJS): $(OBJECT_DIR)/%.o : %.c
	mkdir -p $(OBJECT_DIR)
	$(CC) $(CFLAGS) $(addprefix -I , $(INCS)) -c $< -o $@

# $(OBJDIR)/kernel.o: $(SOURCE_DIR)/kernel.c
# 	mkdir -p $(OBJDIR)
# 	$(CC) $(CFLAGS) -c $(SOURCE_DIR)/kernel.c -o $(OBJDIR)/kernel.o

clean:
	rm -rf $(OBJECT_DIR) kernel.bin

run: all
	qemu-system-i386 -kernel $(KERNEL_BIN)

