#include <stdio.h>
#include <stdlib.h>
#include "../lib/queue.h"

// Declaração das structs
typedef struct cliente{
	int codigoCliente;
	int operacao;
	int valor;
	int saldo;
	int quantidadeOperacoes; 
} Client;

typedef struct no{
	Client client;
	struct tree *right;
	struct tree *left;
	struct tree *dad;
	int height;
	int level;
} Node;

typedef struct queue{
	Node * node; 	
	struct queue * next;
	struct queue * begin;
	struct queue * end;
	int size;
} Queue; 

Queue * defineQueue(){
	Queue * queue = (Queue *)malloc(sizeof(Queue));
	if (!queue){
		perror(ERROR);
		exit(EXIT_FAILURE); 
	} else{
		queue->begin = NULL;
		queue->end = NULL;
		queue->next = NULL;
		queue->size = ZERO;
		return queue;
	}
}

Queue * push(Queue * queue, Node * newNode){
	Queue * new = (Queue *)malloc(sizeof(Queue)); 
	if (!new){
		perror(ERROR); 
		exit(EXIT_FAILURE);
	} else{
		new->node = newNode; 
		new->next = NULL;
		if (isEmpty(queue)){
			queue->begin = new;
		} else
			queue->end->next = new;
		queue->size += ONE;
		queue->end = new;
	}
	return queue; 
}

void pop(Queue * queue){
	Queue *aux;
	if (isEmpty(queue)){
		clearQueue(queue);
	} else{
		aux = queue->begin;
		queue->begin = aux->next; 		 
	}
	queue->size -= ONE;
	free(aux);
}
	
int isEmpty(Queue *queue){
	return (queue->begin == NULL); 
}

Node * front (Queue * queue){
	return !isEmpty(queue)? queue->begin->node: NULL; 
}

Node * back (Queue * queue){
	return !isEmpty(queue)? queue->end->node: NULL;  
}

int size(Queue * queue){
	return queue->size;
}

void clearQueue(Queue * queue){
	if (queue)
		free(queue); 
}
