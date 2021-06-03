nasm asm_boot_sect.asm -f bin -o asm_boot_sect.bin &&
qemu-system-x86_64 -drive file=asm_boot_sect.bin,format=raw,index=0,media=disk;
