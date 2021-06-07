
[org 0x7c00]

mov bx, _HELLO_MSG_
call _puts 

mov bx, _GOODBYE_MSG_
call _puts

idle:
	jmp $

%include "./include/_puts.asm"

_HELLO_MSG_:
	db 'Hello, World!', 0

_GOODBYE_MSG_:
	db 'Goodbye', 0

times 510-($-$$) db 0
dw 0xaa55

