[org 0x500]
%include "asm/idttab.asm"

;interupt handlers:
;is 1024 bytes

times (1024+2048)-($-$$) db 0