# Makefile do Trabalho de Estrutura de Dados e Algoritmos I - MATA40
# Simulação de Agência Bancária Otimizada utilizando conceito de árvore binária AVL
# Maiores detalhes do desenvolvimento, vide https://github.com/gustavooquinteiro/SearchBinaryTree

# Nome do projeto e do executável encontrado no diretório corrente após compilação
PROJ_NAME = SearchBinaryTree

# Arquivos .c encontrados em src/
C_SOURCE = $(wildcard ./src/*.c)

# Arquivos .h encontrados em lib/
H_SOURCE = $(wildcard ./lib/*.h)

# Arquivos objetos .o encontrados em obj/ após compilação
OBJ = $(subst .c,.o,$(subst src,obj,$(C_SOURCE)))

# Compilador utilizado em testes: gcc (GCC) 7.2.1 20171224  
CC = gcc

# Flags utilizadas na compilação
CC_FLAGS = -c \
           -g \
           -Wall \
           -Wextra \
           -Werror \
           -Wpedantic \

# Comando de construção de diretório
MKDIR = mkdir -p
						
# Comando de limpeza de alvos 
RM = rm -rf

# Regras de compilação
all: objFolder $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	@ echo '[BUILD] Construindo binário $@...'
	@ $(CC) $^ -o $@
	@ echo '[DONE] Build completo'
	
./obj/%.o: ./src/%.c ./lib/%.h
	@ echo '[COMPILE] Compilando objeto $@...'
	@ $(CC) $< $(CC_FLAGS) -o $@

# Regra de criação de diretório para os objetos		
objFolder:
	@ echo '[MAKE] Criando diretório para objetos...'
	@ $(MKDIR) obj
	@ echo '[DONE] Diretório criado'

# Regra de limpeza de objetos e executável	
clean:
	@ echo '[CLEAN] Limpando sujeira criada...'
	@ $(RM) obj $(PROJ_NAME) *~
	@ echo '[DONE] Limpeza concluída'
	
.PHONY: all clean
