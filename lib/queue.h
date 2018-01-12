#ifndef FILA_H
#define FILA_H

#define ERROR "Dynamic allocation failed"

typedef struct queue Queue;
typedef struct no Node;
typedef struct cliente Client;

Queue * defineQueue();
Queue * push(Queue * queue, Node * newNode);
void pop(Queue * queue);
int isEmpty(Queue * queue);
Node * front (Queue * queue);
void clearQueue(Queue * queue);
#endif
