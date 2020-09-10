all: $(kernel_objs)

%.asm.o: %.asm
	$(AS) $(AS_FLAGS) $(PWD)$< -o $(build_dir)$@

%.c.o: %.asm
	$(CC) $(CC_FLAGS) $(PWD)$< -o $(build_dir)$@