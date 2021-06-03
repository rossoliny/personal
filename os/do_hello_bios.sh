nasm hello_bios.asm -f bin -o hello_bios.bin &&
qemu-system-x86_64 -drive file=hello_bios.bin,format=raw,index=0,media=disk;
