#ifndef AVL_H
#define AVL_H

// Definir constantes utéis
#define ZERO 0
#define ONE 1
#define TWO 2

// Definir constantes de fatores de balanceamentos da árvore
#define UNBALANCED_TREE_RIGHT -2
#define UNBALANCED_TREE_LEFT 2
#define BALANCED_TREE_RIGHT -1

typedef struct cliente Client; 
typedef struct tree Node; 

void definirArvore(Node * newNode);
Node * criarNo(Client * novoCliente);
Node * inserirNo(Node * tree, Node * actualNode);
Node * balanceamento(Node * tree);
Node * atualizarCliente(Node * actualNode, Node * tree);
Node * busca(Node * arvore, int chave);
int maximo(int left, int right);
int getAltura(Node * tree);
void listarDecrescente(Node * root);
void listarCrescente(Node * root);
Node * arvoreVazia();
Node * criarCliente(int codigoCliente, int operacao, int valor);
void removerNo(Node * tree, int key);
void mostrarNivel(int level);
Node * getRaiz();
#endif
