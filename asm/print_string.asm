
print_string:
;push all
    pusha
;set ah to the print id
    mov ah, 0x0e
;loop start
loop:
; set al to contain the character at bx
    mov al, [bx]
;run the bios teleprint interrupt
    int 0x10
;increment the pointer
    inc bx
; check if it's a null
    cmp al, 0
;if not then loop
    jne loop
;pop all
    popa
;return
ret