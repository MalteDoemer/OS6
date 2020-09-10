export root_dir := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
export obj_dir := $(root_dir)obj/
export bin_dir := $(root_dir)bin/
export src_dir := $(root_dir)src/
export inc_dir := $(root_dir)src/Headers/

export AS = nasm.exe
export CC = x86_64-elf-gcc.exe
export LD = x86_64-elf-ld.exe

export AS_FLAGS = -f elf64 -g
export CC_FLAGS = -ggdb -m64 -c -ffreestanding -fno-PIE -nostartfiles -nostdlib -std=c99 -I $(inc_dir)
export LD_FLAGS = -T $(root_dir)/link.ld


export loader_files := $(notdir $(shell /usr/bin/find $(src_dir)Loader -type f -path "*.*"))
export loader_objs := $(patsubst %,%.o,$(loader_files))

export kernel_files := $(notdir $(shell /usr/bin/find $(src_dir)Kernel -type f -path "*.*"))
export kernel_objs := $(patsubst %,%.o,$(kernel_files))

export objs := $(loader_objs) $(kernel_objs)

_objs := $(patsubst %,$(obj_dir)/%,$(objs))

all:
	@echo
	@echo
	make -C $(src_dir)/Loader
	@echo
	@echo
	make -C $(src_dir)/Kernel
	@echo
	@echo

clean:
	rm -f $(_objs)