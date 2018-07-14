#include <stdio.h>
#include <stdlib.h>
#include "avl.h"	
#ifndef FILA_H
#define FILA_H

// Definição de constantes para legibilizar código
#define ZERO 0
#define ONE 1
#define MALLOC_ERROR "Dynamic allocation failed"

// Assinaturas das funções e struct
typedef struct queue Queue;

// Função que aloca na memoria uma queue
Queue * defineQueue();

// Função que insere um novo elemento na queue.
Queue * push(Queue * queue, Node * newNode);

// Função que remove o elemento da frente da queue 
Queue * pop(Queue * queue);

// Função que verifica se a queue está vazia
int isEmpty(Queue * queue);

// Função que retorna o elemento da frente da queue
Node * front (Queue * queue);

// Função que retorna o elemento do fim da queue
Node * back(Queue * queue);

// Função que retorna o tamanho da queue
int size(Queue * queue);

// Função que desaloca a queue da memória
void clearQueue(Queue * queue);
#endif
