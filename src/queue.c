#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef struct Arvore{
	int codigoCliente;
	struct Arvore * father; 
	struct Arvore * left;
	struct Arvore * right;
} No;

typedef struct fila{
	No * node; 	
	struct fila * next;
	struct fila * begin;
	struct fila * end;
} Queue; 

void defineQueue(No * node){
	extern Queue definedQueue; 
	definedQueue.end = definedQueue.begin = push(&definedQueue, node);
}

Queue * push(Queue * queue, No * newNode){
	Queue * new = (Queue *)malloc(sizeof(Queue)); 
	if (!new){
		perror(ERROR); 
		exit(TRUE);
	} else{
		new->node = newNode; 
		new->next = NULL;
		if (isEmpty(queue)){
			queue->begin = new;
		} else{
			queue->end->next = new;
		}
		queue->end = new;
	}
	return queue; 
}

void pop(Queue * queue){
	Queue *aux;
	if (isEmpty(queue)){
		queue->end = NULL;
	} else{
		aux = queue->begin;
		queue->begin = aux->next; 		 
		free(aux);
	}
}
	
int isEmpty(Queue *queue){
	return (queue->begin == NULL); 
}

int isNotDefined(){
	return (getQueue() == NULL);
}

Queue * front (Queue * queue){
	if (!isEmpty(queue))
		return queue->begin; 
	return NULL; 
}

Queue * getQueue(){
	static Queue * originalQueue = &definedQueue;
	return originalQueue;
}
