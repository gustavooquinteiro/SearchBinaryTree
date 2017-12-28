#ifndef AVL_H
#define AVL_H

#define TRUE 1
#define FALSE 0
#define END 'f'
#define INSERT 'i'
#define SEARCH 'c'
#define REMOVE 'r'
#define ORDER_LIST 'p'
#define CRESCENT_ORDER 'c'
#define DECRESCENT_ORDER 'd'
#define LEVEL_LIST 'n'
#define HEIGHT 'h'
#define ZERO 0
typedef struct Cliente Cliente; 
typedef struct Arvore No; 

void definirArvore(No * newNode);
void criarNo(Cliente * novoCliente);
No * inserirNo(No * tree, No * actualNode);
No * balanceamento(No * tree);
No * atualizarCliente(No * actualNode, No * tree);
No * busca(No * arvore, int chave);
int maximo(int left, int right);
int getAltura(No * tree);
int arvoreVazia();
No * getRaiz();
No * getNo();
void criarCliente(int codigoCliente, int operacao, int valor);
void removerNo(No * nodeToBeRemoved);
#endif
