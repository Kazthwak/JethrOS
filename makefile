all: nasm C_file os_image run

nasm:
	@nasm asm/boot_sect.asm
	@nasm asm/idtc.asm
	@mv asm/boot_sect .
	@mv asm/idtc .
	@cat boot_sect idtc > boot_sect.bin
C_file:
	@sudo python stitch.py
	@gcc -ffreestanding -c toComp.c -o kernel.o 
	@nasm asm/kernel_entry.asm -f elf64 -Wl,-z,max-page-size=0x10 -o kernel_entry.o
	@ld -T link.ld -o kernel.bin kernel_entry.o kernel.o
os_image:
	@cat boot_sect.bin kernel.bin > os-image 
run:
	@qemu-system-x86_64 -drive format=raw,file=os-image 
