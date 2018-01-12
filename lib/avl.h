#ifndef AVL_H
#define AVL_H

// Definir constantes utéis
#define MINUS_ONE -1
#define ZERO 0
#define ONE 1
#define UNBALANCED_TREE_MODULE 2

// Definir constantes de fatores de balanceamentos da árvore
#define UNBALANCED_TREE_LEFT -2
#define UNBALANCED_TREE_RIGHT 2
#define BALANCED_TREE_RIGHT -1
#define BALANCED_TREE_LEFT 1

typedef struct cliente Client; 
typedef struct no Node; 
typedef struct tree AVLtree;

Node * definirRaiz(AVLtree * arvore, Node * node); 
AVLtree * definirArvore();
Node * criarNo(Client * novoCliente);
Node * inserirNo(Node * arvore, Node * actualNode);
Node * balanceamento(Node * arvore);
Node * atualizarCliente(Node * actualNode, Node * arvore);
Node * busca(Node * arvore, int chave);
int maximo(int left, int right);
int getAltura(Node * arvore);
Node * listarDecrescente(Node * root);
Node * listarCrescente(Node * root);
Node * criarCliente(int codigoCliente, int operacao, int valor);
//void removerNo(Node * arvore, int key);
void mostrarNivel(int level, AVLtree * tree);
Node * isTreeEmpty(AVLtree * tree);
AVLtree * isDefined(AVLtree * tree);
Node * getRaiz(AVLtree * tree);
Node * isRootDefined(AVLtree * tree);

Node * rotacaoDireita(Node * x);
Node * rotacaoEsquerda(Node * x);
Node * rotacaoEsquerdaDireita(Node * x);
Node * rotacaoDireitaEsquerda(Node * x);
Node * remocaoNo(Node * raiz, Client x);
Node * getMinimo(Node * x);
#endif
