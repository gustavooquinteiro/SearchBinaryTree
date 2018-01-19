#include "client.h"
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

// Assinaturas das funções e structs
typedef struct no Node;
typedef struct tree AVLtree;

AVLtree * definirRaiz(AVLtree * arvore, Client * client);
AVLtree * definirArvore();
Node * criarNo(Client * novoCliente);
Node * inserirNo(Node * raiz, Client * client);
Node * balanceamento(Node * arvore);
Node * busca(Node * arvore, int chave);
int maximo(int left, int right);
int calculaAltura(Node * arvore);
Node * isTreeEmpty(AVLtree * tree);
AVLtree * isDefined(AVLtree * tree);
Node * getRaiz(AVLtree * tree);
Node * isRootDefined(AVLtree * tree);
int getAlturaArvore(AVLtree * arvore);
Node * rotacaoDireita(Node * x);
Node * rotacaoEsquerda(Node * x);
Node * rotacaoDuplaDireita(Node * x);
Node * rotacaoDuplaEsquerda(Node * x);
Node * removerNo(Node * raiz, int x);
Node * getMinimo(Node * x);
int calculaBalanceFactor(Node * no);
int calculaNivel(Node * raiz);
int getQuantidadeNos(AVLtree * arvore);
Node * getLeftSon(Node * raiz);
Node * getRightSon(Node * raiz);
int getNivel(Node *  no);
void atualizaQuantidadeNo(AVLtree * arvore);
Client * getClient(Node * no);
void atualizaArvore(AVLtree * arvore);
int calculaQuantidadeNos(Node * raiz);
AVLtree * atualizarRaiz(AVLtree * arvore, int chave);
void cleanTree(AVLtree * arvore);
void cleanNode(Node * node);

#endif
