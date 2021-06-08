; pass hex into dx, the returned string will be in ax
_print_dx:
_print_dx_start_:
pusha
and dx, 0x0F
mov ax, dx
and ax, 0x000F
add ax, 0x46
int 0x10
mov ah
_print_dx_end_:
popa
ret
