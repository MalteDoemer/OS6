#ROOT = $(dir $(abspath $(lastuint16_t $(MAKEFILE_LIST))))

LOADER = bin/loader.bin
KERNEL = bin/kernel.bin
OS_BIN = bin/os.bin
OS_ELF = obj/os.o

HDD_IMAGE = userland/hdd.img

AS = nasm.exe
CC = x86_64-elf-gcc.exe
LD = x86_64-elf-ld.exe
OBJCOPY = x86_64-elf-objcopy.exe
QEMU = qemu-system-x86_64.exe

AS_FLAGS = -f elf64 -g
CC_FLAGS = -ggdb -m64 -c -ffreestanding -fno-PIE -nostartfiles -nostdlib -std=c99 -Wno-packed-bitfield-compat -I src/Headers
LD_FLAGS = -T link.ld


KERNEL_OBJS = assembly.o clock.o common.o gdt.o idt.o isr.o kernel.o keyboard.o kheap.o monitor.o paging.o tables.o process.o
LOADER_OBJS = boot.o

KERNEL_OBJS := $(patsubst %,obj/Kernel/%,$(KERNEL_OBJS))
LOADER_OBJS := $(patsubst %,obj/Loader/%,$(LOADER_OBJS))

OBJS = $(KERNEL_OBJS) $(LOADER_OBJS)


$(OS_BIN): $(KERNEL) $(LOADER)
	cat $(LOADER) $(KERNEL) > $@

$(KERNEL): $(OS_ELF)
	$(OBJCOPY) -R .loader -O binary $< $@

$(LOADER): $(OS_ELF)
	$(OBJCOPY) -j .loader -O binary $< $@

$(OS_ELF): $(OBJS)
	$(LD) $(LD_FLAGS) $(OBJS) -o $@

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) $< -o $@

obj/%.o: src/%.asm
	@mkdir -p $(dir $@)
	$(AS) $(AS_FLAGS) $< -o $@

run: $(OS_BIN)
	$(QEMU) $(OS_BIN) -drive file=$(HDD_IMAGE),if=ide

debug: $(OS_BIN)
	$(QEMU) $(OS_BIN) -S -gdb tcp::9000 -drive file=$(HDD_IMAGE),if=ide

clean:
	rm -f $(OBJS) $(OS_ELF) $(LOADER) $(KERNEL) $(OS_BIN)