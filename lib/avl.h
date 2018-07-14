#include <stdio.h>
#include <stdlib.h>
#include "client.h"
#ifndef AVL_H
#define AVL_H

// Definição de constantes utéis ao código
#define ZERO 0
#define ONE 1
#define TWO 2

// Struct de cada nó da arvore
typedef struct no Node;

// Struct da arvore
typedef struct tree AVLtree;

// Função que aloca na memória uma árvore AVL
AVLtree * definirArvore();

// Função que aloca na memória um nó com os atributos do cliente
Node * criarNo(Client * novoCliente);

int maximo(int left, int right);

// Função que define a raiz da arvore
AVLtree * definirRaiz(AVLtree * arvore, Client * client);

// Função que insere o nó na arvore
Node * inserirNo(Node * raiz, Client * client);

// Função que faz o balanceamento da arvore, seguindo o critério AVL
Node * balanceamento(Node * arvore);

// Função de busca da chave na arvore
Node * busca(Node * arvore, int chave);

// Função que retorna a altura de determinado no da arvore
int calculaAltura(Node * arvore);

// Função que verifica se a árvore está vazia
Node * isTreeEmpty(AVLtree * tree);

// Função que retorna a raiz de uma árvore
Node * getRaiz(AVLtree * tree);

// Função que verifica se a árvore tem uma raiz
Node * isRootDefined(AVLtree * tree);

// Função que retorna a altura da árvore
int getAlturaArvore(AVLtree * arvore);

// Função que realiza a rotação a direita de um nó
Node * rotacaoDireita(Node * x);

// Função que realiza a rotação a esquerda de um nó
Node * rotacaoEsquerda(Node * x);

// Função que realiza a dupla rotação a direita de um nó
Node * rotacaoDuplaDireita(Node * x);

// Função que realiza a dupla rotação a esquerda de um nó
Node * rotacaoDuplaEsquerda(Node * x);

// Função que remove um nó, que contenha chave igual a x, da árvore
Node * removerNo(Node * raiz, int x);

// Função que retorna o menor valor, a partir de um nó fornecido
Node * getMinimo(Node * x);

/* Função que calcula o fator de balanceamento de um nó
 * Fator de balanceamento utilizado = altura da esquerda - altura da direita */
int calculaBalanceFactor(Node * no);

// Função que calcula o nível de um nó
int calculaNivel(Node * raiz);

// Função que retorna a quantidade de nós de uma árvore
int getQuantidadeNos(AVLtree * arvore);

// Função que retorna o filho a esquerda de um nó
Node * getLeftSon(Node * raiz);

// Função que retorna o filho a direita de um nó
Node * getRightSon(Node * raiz);

// Função que retorna um cliente de um nó
Client * getClient(Node * no);

// Função que redefine a raiz da arvore
void atualizaArvore(AVLtree * arvore);

// Função que calcula a quantidade de nós de uma árvore
int calculaQuantidadeNos(Node * raiz);

// Função que redefine a raiz da arvore
AVLtree * atualizarRaiz(AVLtree * arvore, int chave);

// Função que retira a arvore da memória
void cleanTree(AVLtree * arvore);

// Função que retira o nó da memória, assim como o cliente contido
void cleanNode(Node * nodeToRemove);

// Função que retorna o sucessor do nó
Node * sucessor(Node * raiz);


#endif
