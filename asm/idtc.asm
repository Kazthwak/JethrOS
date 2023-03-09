[bits 32]
%include "asm/idttab.asm"
;supposed to be a static idt built on compile time, but I realised that was a garbage idea

;interupt handlers:
;is 1024 bytes
; [bits 32]
; [extern Qshutdown]
; mov eax, Qshutdown
; and eax, 0xffff 

db "This is a 1024 byte empty section padded with As "
times (1024+2048)-($-$$) db 0x41