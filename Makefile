#
all: main.o avl.o
	gcc -o main.o avl.o -c AgenciaBancariaOtimizada
avl.o:
	gcc -g avl.c
main.o: