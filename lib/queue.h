#ifndef FILA_H
#define FILA_H

#define ERROR "Dynamic allocation failed"

typedef struct queue Queue;
typedef struct tree Node;
typedef struct cliente Client;

Queue * defineQueue();
Queue * push(Queue * queue, Node * newNode);
void pop(Queue * queue);
int isEmpty(Queue * queue);
int isNotDefined();
Node * front (Queue * queue);

#endif
