./../../WinGCC/bin/i686-elf-as boot.s -o boot.o
./../../WinGCC/bin/i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O0
./../../WinGCC/bin/i686-elf-gcc -c libc.c -o libc.o -std=gnu99 -ffreestanding -O0
./../../WinGCC/bin/i686-elf-gcc -c keyboard.c -o keyboard.o -std=gnu99 -ffreestanding -O0
./../../WinGCC/bin/i686-elf-gcc -c video.c -o video.o -std=gnu99 -ffreestanding -O0
./../../WinGCC/bin/i686-elf-gcc -T linker.ld -o kernel.com -ffreestanding -O0 -nostdlib boot.o libc.o video.o keyboard.o kernel.o -lgcc