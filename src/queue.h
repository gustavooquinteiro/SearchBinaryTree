#ifndef FILA_H
#define FILA_H

#define TRUE 1
#define FALSE 0
#define ERROR "Dynamic allocation failed"

typedef struct Arvore No;
typedef struct fila Queue;

void defineQueue(No * node);
Queue * push(Queue * queue, No * node);
void pop(Queue * queue);
int isEmpty(Queue * queue);
int isNotDefined();
Queue * getQueue();
Queue * front (Queue * queue);

#endif
