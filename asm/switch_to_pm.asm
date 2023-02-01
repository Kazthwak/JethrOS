[bits 16]

db 0x41
idtdef: db 0x08
db 00
dw 00000000

; Switch to protected mode
switch_to_pm:


	push ax
	mov ax, 0x2401
	int 0x15
	pop ax
	cli
pusha
lidt [idtdef]
popa
	lgdt [gdt_descriptor]

	mov eax, cr0
	or eax, 0x1
	mov cr0, eax

	jmp CODE_SEG:init_pm

[bits 32]
init_pm:
	mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ebp, 0x90000
	mov esp, ebp

	call BEGIN_PM