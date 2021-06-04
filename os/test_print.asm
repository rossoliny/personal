
[org 0x7c00]

mov bx, _HELLO_MSG_
call print_str

;mov bx, _GOODBYE_MSG_
;call print_str

jmp $

; %include "include/print_str.asm"
; print null terminated string
; string addr must be in bx
print_str:
xor cx, cx
print_str_loop:
	add bx, cx
	mov al, [bx]
	cmp al, 0
	je print_str_end
	int 0x10
	inc cx
	jmp print_str_loop	

print_str_end:
ret

_HELLO_MSG_:
	db 'Hello, World', 0

_GOODBYE_MSG_:
	db 'Goodbye', 0

times 510-($-$$) db 0
dw 0xaa55

