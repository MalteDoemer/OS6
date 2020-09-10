all: $(loader_objs)

$(loader_objs): %.asm.o: %.asm
	$(AS) $(AS_FLAGS) $(PWD)$< -o $(build_dir)$@

$(loader_objs): %.c.o: %.asm
	$(CC) $(CC_FLAGS) $(PWD)$< -o $(build_dir)$@