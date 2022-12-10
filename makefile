all: nasm C_file os_image run

nasm:
	@nasm boot_sect.asm
	@mv boot_sect boot_sect.bin
C_file:
	@sudo python stitch.py
	@gcc -ffreestanding -c toComp.c -o kernel.o 
	@nasm kernel_entry.asm -f elf64 -o kernel_entry.o
	@ld -o kernel.bin -Ttext 0x1000 kernel_entry.o kernel.o --oformat binary
os_image:
	@cat boot_sect.bin kernel.bin > os-image 
run:
	@qemu-system-x86_64 -drive format=raw,file=os-image 
