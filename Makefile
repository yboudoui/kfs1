NAME=dyan_os
# Makefile
CC=i386-elf-gcc
LD=i386-elf-ld
AS=i386-elf-as



CFLAGS= \
-O2 \
-ffreestanding \
-nostdlib \
-fno-builtin \
-fno-exceptions \
-fno-stack-protector \
-nodefaultlibs \


LDFLAGS=-T linker.ld

BUILD_DIR=build
OBJECT_DIR=$(BUILD_DIR)/obj

SOURCE_DIR=code/src
INCLUDE_DIR=code/inc

######################################################

SRCS_KERNEL		= $(addprefix kernel/, \
	bootloader_screen.c \
	kernel.c \
)

SRCS_KEYBOARD	= $(addprefix keyboard/, \
	keyboard.c \
)

SRCS_MATH		= $(addprefix math/, \
	vectors.c \
)

SRCS_READLINE	= $(addprefix readline/, \
	readline_operation.c \
)

SRCS_SHELL		= $(addprefix shell/, \
	shell_input_handlers.c \
	shell.c \
)

SRCS_STD_IO		= $(addprefix std_io/, \
	std_io.c \
)

SRCS_TERMINAL	= $(addprefix terminal/, \
	ecma48.c \
	terminal_string.c \
	terminal.c \
)

SRCS_UI			= $(addprefix ui/, \
	box.c \
)

SRCS_UTILS		= $(addprefix utils/, \
	buffer.c \
	abs.c \
	itoa_base.c \
	atoi.c \
	memset.c \
	memcpy.c \
	memmove.c \
	printf.c \
	strcmp.c \
	strlen.c \
)

SRCS_VGA		= 	$(addprefix vga/, \
	cursor.c \
	vga.c \
)

######################################################

SRCS= $(addprefix $(SOURCE_DIR)/, \
	$(SRCS_KERNEL)			\
	$(SRCS_KEYBOARD)		\
	$(SRCS_MATH)			\
	$(SRCS_READLINE)		\
	$(SRCS_SHELL)			\
	$(SRCS_STD_IO)			\
	$(SRCS_TERMINAL)		\
	$(SRCS_UI)				\
	$(SRCS_UTILS)			\
	$(SRCS_VGA)				\
	main.c \
)

INCS = $(addprefix $(INCLUDE_DIR)/, \
	ft_printf \
	hardware_io \
	kernel \
	keyboard \
	math \
	readline \
	shell \
	std_io \
	terminal \
	ui \
	utils \
	vga \
)

OBJS = $(patsubst $(SOURCE_DIR)/%.c, $(OBJECT_DIR)/%.o, $(SRCS)) $(OBJECT_DIR)/boot.o

KERNEL_BIN=$(BUILD_DIR)/$(NAME).bin


all: $(KERNEL_BIN)
	@echo "Project builted"

$(KERNEL_BIN): $(OBJS)
	@$(LD) $(LDFLAGS) -o $(KERNEL_BIN) $(OBJS)
	@echo $(KERNEL_BIN)

$(OBJECT_DIR)/boot.o: $(SOURCE_DIR)/boot.s
	@mkdir -p $(OBJECT_DIR)
	@$(AS) $(SOURCE_DIR)/boot.s -o $(OBJECT_DIR)/boot.o
	@echo $@

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(addprefix -I , $(INCS)) -c $< -o $@
	@echo $@

clean:
	@rm -rf $(BUILD_DIR)
	@echo "Project cleaned"

re: clean all

iso: all
	@mkdir -p $(BUILD_DIR)/isodir/boot/grub
	@cp $(BUILD_DIR)/$(NAME).bin $(BUILD_DIR)/isodir/boot/$(NAME).bin
	@cp code/grub.cfg $(BUILD_DIR)/isodir/boot/grub/grub.cfg
	@grub-mkrescue -o $(BUILD_DIR)/$(NAME).iso $(BUILD_DIR)/isodir

run: all
	qemu-system-i386 -k en-us -kernel $(KERNEL_BIN)

runiso: iso
	qemu-system-i386 -k en-us -cdrom $(BUILD_DIR)/$(NAME).iso

