#ifndef FILA_H
#define FILA_H

#define TRUE 1
#define FALSE 0

typedef struct fila Queue;

void defineQueue();
int push(Queue * queue, No node);
int pop(Queue * queue);
int isEmpty(Queue * queue);
int isNotDefined();
Queue * getQueue();
Queue * front (Queue * queue);
#endif
