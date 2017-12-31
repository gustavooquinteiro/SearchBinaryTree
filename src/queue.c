#include <stdlib.h>
#include <stdio.h>
#include "avl.h"
#include "queue.h"

typedef struct Arvore{
	int codigoCliente;
	struct Arvore * father; 
	struct Arvore * left;
	struct Arvore * right;
} No;

typedef struct fila{
	No node; 	
	struct fila * next;
	struct fila * begin;
	struct fila * end;
} Queue; 

void defineQueue(){
	extern Queue queue; 
	queue.begin = NULL;
	queue.end = NULL;
}

int push(Queue * queue, No newNode){
	Queue * new = (Queue *)malloc(sizeof(Queue)); 
	if (new == NULL)
		return FALSE;
	new->node = newNode; 
	new->next = NULL;
	if (isEmpty(queue)){
		queue->begin = new;
	} else{
		queue->end->next = new;
	}
	queue->end = new;
	return TRUE; 
}

int pop(Queue * queue){
	Queue *aux;
	if (isEmpty(queue)){
		queue->end = NULL;
		return FALSE;
	}
	aux = queue->begin;
	queue->begin = aux->next; 		 
	free(aux);
	return TRUE;
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
	Queue * originalQueue = & queue;
	return originalQueue;
}
