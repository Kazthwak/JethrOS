[bits 32]
; SECTION .idt
; %include "asm/idtc.asm"

SECTION .ke
; mov dx, 0x604
; mov ax, 0x2000
; out dx, ax

;hang to test
; jmp $
;jump after the message
extern exception_handler

mov [0x500], dword exception_handler
; jmp $
jmp pms
;message so I can find in ram
dd "JethrOS"

;copy-pasted idt code ------------------------------------------
; Loads the IDT defined in '_idtp' into the processor.
global idt_load
idt_load:
    lidt [0x7000]
	ret
	; jmp $	

extern Qshutdown
global idt_test
idt_test:
	int 0x0
	call Qshutdown

;after the message
pms:
; [org 0x1fff]
; hlt
; db 0x43
; jmp $
; dd "THIS IS THE START OF KERNEL ENTRY"
;jnmp to idt initialisation
;include the idt setup code
; #an antiquity no longer used
; %include "asm/idt.asm"


;testintg
; Ensures that we jump straight into the kernel ’s entry function.
[extern main] ; Declate that we will be referencing the external symbol ’ main ’,
; so the linker can substitute the final address
call main ; invoke main () in our C kernel
jmp $ ; Hang forever when we return from the kernel
