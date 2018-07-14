#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "client.h"
#include "queue.h"

#ifndef MAIN_H
#define MAIN_H

// Definição de constantes
#define END 'f'
#define INSERT 'i'
#define SEARCH 'c'
#define REMOVE 'r'
#define LEVEL_LIST 'n'
#define HEIGHT 'h'

#define ORDER_LIST 'p'
#define DECRESCENT_ORDER 'd'

#define FOUND_KEY_MESSAGE "existe no com chave:"
#define NOT_FOUND_KEY_MESSAGE "nao existe no com chave:"

// Função que insere um nó com um cliente na árvore
void insereNo(AVLtree * tree);

// Função que busca determinada chave na árvore e mostra na tela mensagem informativa
void buscaNo(AVLtree * tree);

// Função que remove determinada chave da árvore, se essa chave existir
void removeNo(AVLtree * tree);

// Função que lista os nós segundo ordem inserida
void listarNos(AVLtree * tree);

// Função que lista determinado nível da árvore, se nível existente
void listarNivel(AVLtree * tree);

// Função que mostra a altura da arvore
void mostrarAltura(AVLtree * tree);

// Função que exibe o relatorio final segundo a ordem de remoção da raiz
void exibeRelatorio(AVLtree * tree);

// Função que lista todos os nós da arvore em ordem crescente
void listarCrescente(Node * raiz);

// Função que lista todos os nós da arvore em ordem decrescente
void listarDecrescente(Node * raiz);

#endif
