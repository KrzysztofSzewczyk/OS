./../../WinGCC/bin/i686-elf-as boot.s -o boot.o
./../../WinGCC/bin/i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O0 -Wall -Wextra
./../../WinGCC/bin/i686-elf-gcc -T linker.ld -o kernel.com -ffreestanding -O0 -nostdlib boot.o kernel.o -lgcc