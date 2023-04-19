;tell nasm where thw code starts
[org 0x7c00]

KERNEL_SECTS equ 0x1d

;kernel should be loaded at 0x7e00
KERNEL_OFFSET equ 0x7e00
;but jump to 0x8800
KERNEL_OFFSETj equ 0x9000

;store the boot drive
	mov [BOOT_DRIVE], dl
;setup stack
	mov bp, 0xffff
	mov sp, bp

;print that U have entered real mode
	mov bx, MSG_REAL_MODE
	call print_string


;load the kernel
jmp load_kernel
	kl:

;switch to protected mode
	call switch_to_pm

;if this returns, there has been an error
	jmp $

;include some stuff
%include "asm/print_string.asm"
%include "asm/disk_load.asm"
%include "asm/gdt.asm"
%include "asm/print_string_pm.asm"
%include "asm/switch_to_pm.asm"

;32 bit code
[bits 32]
;closes the computer in qemu
closeqt:
mov dx, 0x604
mov ax, 0x2000
out dx, ax

[bits 16]
;same but 16 bit
closeq:
mov dx, 0x604
mov ax, 0x2000
out dx, ax

;load the kernel
load_kernel:

;print the msg
	mov bx, MSG_LOAD_KERNEL
	; call print_string
;tell the code where to load the code
    mov bx, 0x7e00
;how many sectors to load
	mov dh, KERNEL_SECTS
	;sector to start on
	mov ah, 0x4
	; mov dh, 0x5
	;set dl to contain the drive booted from
	mov dl, [BOOT_DRIVE]

;load the disk
call disk_load
dlr:
; call closeq
; ;push everythong the stack so I dont break things
; 	pusha
; 	;load the idt from drive
; 	mov ah, 2
; 	mov al, 9
; 	mov ch, 0
; 	mov dh, 0
; 	mov dl, [BOOT_DRIVE]
; 	;to here
; ;loads it at 0x700. dont know why but...
; 	mov bx, 0x100
; 	mov cl, 2
; 	int 0x13
; 	popa





;;change video mode to pixel
pusha
mov ah, 0x00
mov al, 0x13
int 0x10
popa


;return
	jmp kl

[bits 32]

;print that U R in protected mode
BEGIN_PM:
	mov ebx, MSG_PROT_MODE
	; call print_string_pm
	; jmp $
	; int 0x0
	; jmp $
	; jmp closeqt
	; jmp $
	;jump to the kernel entry
	call KERNEL_OFFSETj
	;hang if return but should not happen and this probably wont be in ram if it does
	jmp $

;debug function
[bits 16]
debug:
;add 0x30 to cl to turn num into char
add cl, 0x30
;set al to cl
mov al, cl
;set ah to the correct interupt num
mov ah, 0x0e
;invoke intterupt to print
int 0x10
;hang
jmp $

;boot drive storage
BOOT_DRIVE db 0
;messages
MSG_REAL_MODE db "Started in 16-bit Real Mode", 0
MSG_PROT_MODE db "3", 0
MSG_LOAD_KERNEL db "L", 0
;boot sector padding
times 510-($-$$) db 0
;magic number
dw 0xaa55
;idt
;is 2048 bytes

db 0x41
times 2048-($-$$) db 0x0
