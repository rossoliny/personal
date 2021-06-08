; print null terminated string
; string addr must be in bx
_puts:
_start_puts_:
pusha
mov ah, 0x0e
_puts_loop_1_start_:
	mov al, [bx]
	cmp al, 0
	je _puts_loop_1_end_
	int 0x10
	inc bx
	jmp _puts_loop_1_start_
_puts_loop_1_end_:
_end_puts_:
mov al, 0xA
int 0x10
mov al, 0xD
int 0x10
popa
ret

