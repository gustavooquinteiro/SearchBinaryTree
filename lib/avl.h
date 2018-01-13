#ifndef AVL_H
#define AVL_H

// Definir constantes utéis
#define ZERO 0
#define ONE 1

// Definir constantes de fatores de balanceamentos da árvore
#define TWO 2

#define UNBALANCED_TREE_LEFT -2

#define BALANCED_TREE_LEFT -1
#define BALANCED_TREE_RIGHT 1

typedef struct cliente Client; 
typedef struct no Node; 
typedef struct tree AVLtree;

AVLtree * definirRaiz(AVLtree * arvore, Node * node); 
AVLtree * definirArvore();
Node * criarNo(Client * novoCliente);
Node * inserirNo(Node * arvore, Node * actualNode);
Node * balanceamento(Node * arvore);
Node * atualizarCliente(Node * actualNode, Node * arvore);
Node * busca(Node * arvore, int chave);
int maximo(int left, int right);
int calculaAltura(Node * arvore);
Node * criarCliente(int codigoCliente, int operacao, int valor);
Node * isTreeEmpty(AVLtree * tree);
AVLtree * isDefined(AVLtree * tree);
Node * getRaiz(AVLtree * tree);
Node * isRootDefined(AVLtree * tree);
int getAlturaArvore(AVLtree * arvore);
Node * rotacaoDireita(Node * x);
Node * rotacaoEsquerda(Node * x);
Node * rotacaoEsquerdaDireita(Node * x);
Node * rotacaoDireitaEsquerda(Node * x);
Node * removerNo(Node * raiz, int x);
Node * getMinimo(Node * x);
int calculaBalanceFactor(Node * no);
int calculaNivel(Node * raiz);
int getQuantidadeNos(AVLtree * arvore);
Node * getLeftSon(Node * raiz);
Node * getRightSon(Node * raiz); 
int getNivel(Node *  no);
long long int getClientCode (Node * no);
long long int getClientOperationsQuantity(Node * no);
long long int getClientValue(Node * no);
void atualizaQuantidadeNo(AVLtree * arvore);

#endif
