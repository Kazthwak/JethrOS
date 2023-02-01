	; mov bx, MSG_LOAD_KERNEL
	; call print_string
    ; mov bx, KERNEL_OFFSET
	; mov dh, 0x1;c
	; ; mov dh, 0x5
	; mov dl, [BOOT_DRIVE]
	; call disk_load


; disk_load:
; pusha

; ;setup disk section
;      mov ch, 0x00
;      mov dh, 0x00
; ;the sector to read
;      mov cl, 0x06
; ;the loop start
; .loop:
; ;check if dh is 0
; cmp dh, 0
; ;if so then end
; jle .end
; ; set the interupt to disk read
; mov ah, 0x02
; ;read 1 sector
; mov al, 1
; ;disk load interupt
; int 0x13

; ;check for disk read error:
; jc disk_error

; ;decrement the number of sectors to read
; dec dh
; ;increment the sector being read
; inc cl
; ;add 512 to the address to load to
; add bx, 512

; jmp .loop
; .end:
; popa
; ret

;#==>--TODO--<==#
;rubber duck debugging

disk_load:
pusha
;dl remains the same and is drive
;secotr
mov cl, ah
;ah is operation to do
mov ah, 0x02
;al is no of sectors
mov al, dh
;cylinder
mov ch, 0
;head
mov dh, 0
;dl is already set


int 0x13
jc disk_error
popa
jmp dlr

; load DH sectors to ES:BX from drive DL
;store of dh
store: dd "A"
;current sector being read
sam: dd byte 0x00
db 0

disk_loadold:
;set the sector to read to 5
mov [sam], byte 0x05
;push everything to the stack
pusha
;loop start
.loop:
;check if we've loaded dh sectors
cmp dh, 0x0
;if we have, then end
jle end
;decrease dh
dec dh
;increase the sector to read
inc byte [sam]
;store dh in store
mov [store], byte dh
;move dh to contain sam
mov dh, byte [sam]
;push everythining to the stack
pusha
mov cl, dh
;call the disk load function
call disk_loadi
;pop everything
popa
;mov dh to contain store
mov dh, [store]
; add 512 to bx so it goes to the next bit of ram
add bx, 0x200
;go back to the beginning of the loop
jmp .loop
;end
end:
; pop everything
popa
;return
jmp dlr

disk_loadi:

; pudh dx to the stack to preserve it
    push dx

mov cl, dh

;set ah(the interupt number) to 2
    mov ah, 0x02
;load one sector
    mov al, 1
;from beginning of disk
    mov ch, 0x00
    mov dh, 0x00
;at sector dh

;call the debug function to display cl
; call debug

    ; mov cl, 0x06


;run the interrupt
    int 0x13


;if disk error then  jump to the handler
    jc disk_error

deret:
;get dx back
    pop dx
    ;check if number of loaded sectors was one
    cmp al, 1
    ;if not then disk error
    jne disk_error
;return
    ret

disk_error:

tst:
; jmp $

;check if U have run out of sectors
cmp ah, 0x0c
; je deret

    mov bx, DISK_ERROR_MSG
    call print_string
    jmp $

DISK_ERROR_MSG: db "Disk read error!", 0