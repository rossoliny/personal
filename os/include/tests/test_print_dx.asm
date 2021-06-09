
[org 0x7c00]

mov dx, 0xFFFF
call _print_dx

xor dx, dx
call _print_dx

mov dx, 0xAAAA
call _print_dx

idle:
	jmp $

%include "../_print_dx.asm"

times 510-($-$$) db 0
dw 0xaa55
