@echo off

i686-elf-as lib/gdt.S -o gdt.o
i686-elf-as lib/idt.S -o idt.o
i686-elf-gcc -c kmain.c -o kmain.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Wpedantic -Wshadow -Werror -g
i686-elf-gcc -c lib/gdt.c -o gdtf.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Wpedantic -Wshadow -Werror -g
i686-elf-gcc -c lib/tty.c -o ttyf.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Wpedantic -Wshadow -Werror -g
i686-elf-gcc -c lib/idt.c -o idtf.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Wpedantic -Wshadow -Werror -g
i686-elf-gcc -c lib/mem.c -o memf.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Wpedantic -Wshadow -Werror -g
i686-elf-gcc -c lib/pic.c -o picf.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Wpedantic -Wshadow -Werror -g
i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kmain.o ttyf.o gdtf.o gdt.o idtf.o memf.o picf.o idt.o -lgcc -g

echo.
echo Run?
set /p i=Prompt: 
if %i%==y (
start "" "qemu-system-i386" -kernel myos.bin -d int -no-reboot -no-shutdown
) else (
exit /b
)