; pass hex into dx
_print_dx:
_print_dx_start_:
pusha
mov ah, 0x0e

; hex prefix
mov al, 0x30
int 0x0010
mov al, 0x78
int 0x0010

xor cx, cx
_print_dx_loop_:
mov al, dh
and al, 0xF0
shr al, 0x04
cmp al, 0x0A
jl _no_letters_
add al, 0x07
_no_letters_:
add al, 0x30
int 0x0010
shl dx, 0x0004
inc cx
cmp cx, 0x0004
jl _print_dx_loop_

mov al, 0xA
int 0x10
mov al, 0xD
int 0x10

_print_dx_end_:
popa
ret

