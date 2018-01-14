#ifndef FILA_H
#define FILA_H

// Definição de constantes para legibilizar código
#define ZERO 0
#define ONE 1
#define MALLOC_ERROR "Dynamic allocation failed"

// Assinaturas das funções e struct
typedef struct queue Queue;

Queue * defineQueue();
Queue * push(Queue * queue, Node * newNode);
void pop(Queue * queue);
int isEmpty(Queue * queue);
Node * front (Queue * queue);
Node * back(Queue * queue);
void clearQueue(Queue * queue);
int size(Queue * queue);
#endif
