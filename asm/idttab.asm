;idt
;supposed to be a static idt built on compile time, but I realised that was a garbage idea
;is 2048 bytes
; int1isrl: dd word 0x0
; dd word 0x0
; dd byte 0x0
; dd byte 0x8e
; int1isrh: dd word 0x0
db "This is a 2048 byte empty section padded with Bs "



times 2048-($-$$) db 0x42