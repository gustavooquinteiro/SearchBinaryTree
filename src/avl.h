#ifndef AVL_H
#define AVL_H

#define ZERO 0
#define ONE 1

#define UNBALANCED_TREE_RIGHT -2
#define UNBALANCED_TREE_LEFT 2
#define BALANCED_TREE_RIGHT -1
#define BALANCED_TREE_LEFT 1

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
void listarDecrescente(No * root);
void listarCrescente(No * root);
int arvoreVazia();
No * getRaiz();
No * getNo();
void criarCliente(int codigoCliente, int operacao, int valor);
void removerNo(No * nodeToBeRemoved);
int mostrarNivel(int level);
#endif
