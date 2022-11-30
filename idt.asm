; Loads the IDT defined in 'idtp' into the processor.
; This is declared in C as 'extern void idt_load();'


initidt:
jmp idtdone