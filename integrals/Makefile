all: program

program: main.o Tests.o functions.o
	gcc -m32 -o program main.o Tests.o functions.o

main.o: main.c
	gcc -m32  -std=c99 -c main.c

Tests.o: Tests.c
	gcc -m32 -std=c99 -c Tests.c

functions.o: functions.asm
	nasm -f elf32 functions.asm

clean:
	-rm main.o
	-rm Tests.o
	-rm functions.o


