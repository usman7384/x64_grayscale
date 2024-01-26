
clean:
	rm -rf build

build:
	nasm -f elf64 src/filter.asm -o filter.o
	g++ src/main.cpp filter.o -o prog -std=c++11 -no-pie -lX11 -lXext
	mkdir build
	mv prog build/
	mv filter.o build/

test:
	nasm -f elf64 test.asm -o test.o
	g++ test.cpp test.o -o test -std=c++11 -no-pie -lX11 -lXext
	./test

testclean:
	rm -rf test/test.o test/test