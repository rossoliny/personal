;
; A simple boot sector program that demonstrates addressing.
;


; this line tells the ASM where the program will be loaded.
; [org 0 x7c00] 

mov ah, 0x0e ; int 10/ ah = 0eh -> scrolling teletype BIOS routine
; First attempt
mov al, the_secret 
int 0x10 ; Does this print an X?
; No, because it loads the actual offset into al rather than data at that offset

; Second attempt
mov al, [ the_secret ]
int 0x10 ; Does this print an X?
; No, beacuse it stores the data at the offset from the 0x0 address rather than from the begining of the program.

; Third attempt
mov bx, the_secret
add bx, 0x7c00
mov al, [bx]
int 0x10 ; Does this print an X?
; Yes, as BIOS prefers to always load the boot program at addres 0x7c00

; Fourth attempt
mov al, [0x7c1e]
int 0x10 ; Does this print an X?
jmp $ ; Jump forever.
; Yes, as we precalculated the offset by exploring binary.

the_secret :
db "X"

; Padding and magic BIOS number.
times 510 -( $ - $$ ) db 0
dw 0xaa55
