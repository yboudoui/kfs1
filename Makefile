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
--no-entry \
-g


LDFLAGS=-T linker.ld

BUILD_DIR=./build
OBJECT_DIR=$(BUILD_DIR)/obj

SOURCE_DIR=code

######################################################
# Core
######################################################

SRCS_CONTEXT			+= context.c3

SRCS_HARDWARE_IO		+= io.c3

SRCS_HARDWARE_KEYBOARD	+= codepage347.c3
SRCS_HARDWARE_KEYBOARD	+= scancode.c3
SRCS_HARDWARE_KEYBOARD	+= handler.c3
SRCS_HARDWARE_KEYBOARD	+= keyboard.c3

SRCS_HARDWARE_VGA		+= color.c3
SRCS_HARDWARE_VGA		+= frame.c3
SRCS_HARDWARE_VGA		+= cursor.c3

SRCS_KERNEL				+= kernel.c3

SRCS_CORE = \
	$(addprefix core/, \
		$(addprefix context/, $(SRCS_CONTEXT)) \
		$(addprefix hardware/, \
			$(addprefix io/, $(SRCS_HARDWARE_IO))		\
			$(addprefix keyboard/, $(SRCS_HARDWARE_KEYBOARD))	\
			$(addprefix vga/, $(SRCS_HARDWARE_VGA))				\
		) \
		$(addprefix kernel/, $(SRCS_KERNEL)) \
)

######################################################
# Lib
######################################################

SRCS_READLINE	= $(addprefix readline/, \
	readline.c3 \
)

SRCS_SHELL		= $(addprefix shell/, \
	shell.c3 \
)

SRCS_UI			= $(addprefix ui/, \
	box.c3 \
)

SRCS_LIB			= $(addprefix lib/, \
	$(SRCS_READLINE) \
	$(SRCS_SHELL) \
	$(SRCS_UI) \
)

######################################################
# Std
######################################################

SRCS_STD_IO		= $(addprefix io/, \
	std_io.c3 \
)

SRCS_STD_MATH		= $(addprefix math/, \
	math.c3 \
	window.c3 \
	vector.c3 \
)

SRCS_STD_MEMORY		= $(addprefix memory/, \
	buffer.c3 \
	memory.c3 \
)

SRCS_STD_STRING		= $(addprefix string/, \
	printf.c3 \
	string.c3 \
)

SRCS_TERMINAL	= $(addprefix terminal/, \
	ecma48.c3 \
	terminal.c3 \
)

SRCS_STD		= $(addprefix std/, \
	$(SRCS_STD_IO) \
	$(SRCS_STD_MATH) \
	$(SRCS_STD_MEMORY) \
	$(SRCS_STD_STRING) \
	$(SRCS_TERMINAL) \
)

######################################################

SRCS= $(addprefix $(SOURCE_DIR)/, \
	$(SRCS_CORE)		\
	$(SRCS_LIB)		\
	$(SRCS_STD)			\
	main.c3 \
	bootloader_screen.c3 \
	entry.c3 \
	logo42.c3 \
)

KERNEL_BIN=$(BUILD_DIR)/$(NAME).bin

all: $(KERNEL_BIN)
	@echo "Project builted"

$(KERNEL_BIN): c3_obj 
	@$(LD) $(LDFLAGS) -o $(KERNEL_BIN) $(shell find $(OBJECT_DIR) -name '*.o')
	@echo $(KERNEL_BIN)

c3_obj:
	@mkdir -p $(OBJECT_DIR)
	$(CC3) compile-only --obj-out $(OBJECT_DIR) $(SRCS) $(CC_FLAGS)
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

run_debug: all
	qemu-system-i386 -s -S -k en-us -kernel $(KERNEL_BIN)
	