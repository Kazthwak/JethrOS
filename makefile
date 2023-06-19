flag = nodebug

all: run

run: os-image
	@qemu-system-x86_64 -drive format=raw,file=os-image 

makecomp:
	python stitch.py

kernel.o: makecomp
	@gcc -ffreestanding -c toComp.c -o kernel.o -D$(flag)

kernel_entry.o: ./asm
	@nasm asm/kernel_entry.asm -f elf64 -Wl,-z,max-page-size=0x10 -o kernel_entry.o

kernel.bin: kernel_entry.o kernel.o link.ld
	@ld -T link.ld -o kernel.bin kernel_entry.o kernel.o

boot_sect.bin:
	nasm asm/boot_sect.asm
	mv ./asm/boot_sect ./boot_sect.bin


os-image: boot_sect.bin kernel.bin
	@cat boot_sect.bin kernel.bin > os-image
