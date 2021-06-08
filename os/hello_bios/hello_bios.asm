;
; A simple boot sector that prints a message to the screen using a BIOS routine.
;

[org 0x7c00]

mov ah, 0x0e 	; int 10/ ah = 0eh -> scrolling teletype BIOS routine

xor cx, cx

print_string:
	mov bx, __string__
	add bx, cx
	mov al, [bx]
	cmp al, 0
	je idle
	int 0x10
	inc cx
	jmp print_string

idle:
	jmp $			 ; Jump to the current address ( i.e. forever ).

__string__:
	db 'Hello to Ajar from BIOS', 0

;
; Padding and magic BIOS number.
;

times 510-($-$$) db 0	; Pad the boot sector out with zeros
dw 0xaa55 				; Last two bytes form the magic number ,
						; so BIOS knows we are a boot sector.
