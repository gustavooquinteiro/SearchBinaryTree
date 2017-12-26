# Makefile do Trabalho de Estrutura de Dados e Algoritmos I - MATA40
# Simulação de Agência Bancária Otimizada utilizando conceito de árvore binária AVL
# Maiores detalhes do desenvolvimento, vide https://github.com/gustavooquinteiro/SearchBinaryTree

# Nome do projeto
PROJ_NAME = SearchBinaryTree

# Arquivos .c
C_SOURCE = $(wildcard ./src/*.c)

# Arquivos .h
H_SOURCE = $(wildcard ./src/*.h)

# Arquivos objetos .o
OBJ = $(subst .c,.o,$(subst source,objects,$(C_SOURCE)))

# Compilador utilizado GCC 7.2.1 20171128
CC = gcc

# Flags
CC_FLAGS = -c \
					-Wall \
					-Wextra \
					-Werror \
					-Wpedantic \
					-lm  
						
# Comando de limpeza de alvos 
RM = rm -rf

# Regra para compilar tudo 
all: objFolder $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	@ echo [COMPILING] Construindo binários usando GCC linker: $@...
	$(CC) $^ -o $@
	@ echo '[DONE] Construção do projeto ' $(PROJ_NAME) ' concluída'
	
./objects/%.o: ./src/%.c ./src/%.h
	@ echo [COMPILING] Construindo alvo usando GCC linker: $<...
	$(CC) -g $< $(CC_FLAGS) -o $@
	
./objects/main.o: ./src/main.c $(H_SOURCE)
	@ echo [COMPILING] Construindo alvo usando GCC linker: $<...
	$(CC) -g $@ $< $(CC_FLAGS)

objFolder:
	@ echo [MAKE] Criando diretório para objetos... 
	@ mkdir -p objects
	@ echo [DONE] Diretório para objetos criado
	
clean:
	@ echo [CLEAN] Limpando objetos, executável e diretório criados...
	@ $(RM) ./objects/*.o $(PROJ_NAME) *~
	@ rmdir objects
	@ echo [DONE] Limpeza concluída 
	
.PHONY: all clean