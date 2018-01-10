# Makefile do Trabalho de Estrutura de Dados e Algoritmos I - MATA40
# Simulação de Agência Bancária Otimizada utilizando conceito de árvore binária AVL
# Maiores detalhes do desenvolvimento, vide https://github.com/gustavooquinteiro/SearchBinaryTree

# Nome do projeto
PROJ_NAME = SearchBinaryTree

# Arquivos .c
C_SOURCE = $(wildcard ./src/*.c)

# Arquivos .h
H_SOURCE = $(wildcard ./lib/*.h)

# Arquivos objetos .o
OBJ = $(subst .c,.o,$(subst src,obj,$(C_SOURCE)))

# Compilador utilizado 
CC = gcc

# Flags do compilador
CC_FLAGS = -c \
           -Wall \
           -Wextra \
           -Werror \
           -Wpedantic \
           -lm  

# Comando de construção de diretório
MKDIR = mkdir -p
						
# Comando de limpeza de alvos 
RM = rm -rf
RMDIR = rmdir 

all: objFolder $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	@ echo '[BUILD] Construindo executável: $@...'
	@ $(CC) $^ -o $@
	@ echo '[DONE] Build completo'
	
./obj/%.o: ./src/%.c ./lib/%.h
	@ echo '[BUILD] Construindo alvo: $<...'
	@ $(CC) -g $< $(CC_FLAGS) -o $@
	
objFolder:
	@ echo '[MAKE] Criando diretório para objetos...'
	@ $(MKDIR) obj
	@ echo '[DONE] Diretório criado'
	
clean:
	@ echo '[CLEAN] Limpando executável e diretório criados...'
	@ $(RM) ./obj/*.o $(PROJ_NAME) *~
	@ $(RMDIR) obj
	@ echo '[DONE] Limpeza concluída'
	
.PHONY: all clean