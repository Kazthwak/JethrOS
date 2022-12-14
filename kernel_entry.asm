jmp idtdone
jmp initidt
%include "idt.asm"


idtdone:
[bits 32] ; We ’ re in protected mode by now , so use 32 - bit instructions.
; Ensures that we jump straight into the kernel ’s entry function.
[extern main] ; Declate that we will be referencing the external symbol ’ main ’,
; so the linker can substitute the final address

call main ; invoke main () in our C kernel
int 0xff
jmp $ ; Hang forever when we return from the kernel