NAME=dyan_os
# Makefile

CC3=c3c
CC=i386-elf-gcc
LD=i386-elf-ld
AS=i386-elf-as


CC_FLAGS= \
--target elf-x86 \
--use-stdlib=no \
--link-libc=no \
--emit-stdlib=no \
-g


CFLAGS= \
-O2 \
-ffreestanding \
-nostdlib \
-fno-builtin \
-fno-exceptions \
-fno-stack-protector \
-nodefaultlibs \


LDFLAGS=-T linker.ld

BUILD_DIR=./build
OBJECT_DIR=$(BUILD_DIR)/obj

SOURCE_DIR=code/src
INCLUDE_DIR=code/inc

######################################################

SRCS_HARDWARE		= $(addprefix hardware/, \
	io.c3 \
)

SRCS_KERNEL		= $(addprefix kernel/, \
	bootloader_screen.c3 \
	entry.c3 \
)

SRCS_KEYBOARD	= $(addprefix keyboard/, \
	codepage347.c3 \
	scancode.c3 \
	keyboard.c3 \
)

SRCS_READLINE	= $(addprefix readline/, \
	readline.c3 \
)

SRCS_SHELL		= $(addprefix shell/, \
	shell.c3 \
)

SRCS_STD_IO		= $(addprefix std_io/, \
	std_io.c3 \
)

SRCS_TERMINAL	= $(addprefix terminal/, \
	ecma48.c3 \
	terminal.c3 \
)

SRCS_UI			= $(addprefix ui/, \
	box.c \
)

SRCS_UTILS		= $(addprefix utils/, \
	buffer.c3 \
	math.c3 \
	memory.c3 \
	printf.c3 \
	string.c3 \
	vector.c3 \
	window.c3 \
)

SRCS_VGA		= 	$(addprefix vga/, \
	color.c3 \
	frame.c3 \
	cursor.c3 \
	constante.c3 \
)


######################################################

SRCS= $(addprefix $(SOURCE_DIR)/, \
	$(SRCS_HARDWARE)		\
	$(SRCS_KERNEL)			\
	$(SRCS_KEYBOARD)		\
	$(SRCS_READLINE)		\
	$(SRCS_SHELL)			\
	$(SRCS_STD_IO)			\
	$(SRCS_TERMINAL)		\
	$(SRCS_UI)				\
	$(SRCS_UTILS)			\
	$(SRCS_VGA)				\
	main.c3 \
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

C_SRCS	= $(filter %.c, $(SRCS))
C3_SRCS = $(filter %.c3, $(SRCS))

OBJS += $(patsubst $(SOURCE_DIR)/%.c, $(OBJECT_DIR)/%.o, $(C_SRCS))
OBJS += $(OBJECT_DIR)/boot.o

KERNEL_BIN=$(BUILD_DIR)/$(NAME).bin


all: $(KERNEL_BIN)
	@echo "Project builted"

$(KERNEL_BIN): c3_obj $(OBJS) 
	@$(LD) $(LDFLAGS) -o $(KERNEL_BIN) $(shell find $(OBJECT_DIR) -name '*.o')
	@echo $(KERNEL_BIN)

$(OBJECT_DIR)/boot.o: $(SOURCE_DIR)/boot.s
	@mkdir -p $(OBJECT_DIR)
	@$(AS) $(SOURCE_DIR)/boot.s -o $(OBJECT_DIR)/boot.o
	@echo $@

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c 
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(addprefix -I , $(INCS)) -c $< -o $@
	@echo "Compiled " $< " to "$@


c3_obj:
	@mkdir -p $(OBJECT_DIR)
	$(CC3) compile-only --obj-out $(OBJECT_DIR) $(C3_SRCS) $(CC_FLAGS)
	@echo "Compiled " $< " to "$@

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

