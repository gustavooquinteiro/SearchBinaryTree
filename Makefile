# Makefile do Trabalho de Estrutura de Dados e Algoritmos I - MATA40
# Simulação de Agência Bancária Otimizada 
# Maiores detalhes do desenvolvimento, vide https://github.com/gustavooquinteiro/SearchBinaryTree

all: avl.o main.o
	gcc -g avl.o main.o -o AgenciaBancariaOtimizada -Wall -Wextra -Werror -Wpedantic -lm

avl.o:
	gcc -g -c avl.c -Wall -Wextra -Werror -Wpedantic -lm
	
main.o:
	gcc -g -c main.c -Wall -Wextra -Werror -Wpedantic -lm