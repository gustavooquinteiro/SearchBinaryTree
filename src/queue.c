#include <stdio.h>
#include <stdlib.h>
#include "../lib/queue.h"


// Declaração da struct
typedef struct queue{
	Node * node; 	
	struct queue * next;
	struct queue * begin;
	struct queue * end;
	int size;
} Queue; 

/* Função que aloca na memoria uma queue
 * Caso não consiga alocar, lança erro de alocação na saída padrão e termina o programa */
Queue * defineQueue(){
	Queue * queue = (Queue *)malloc(sizeof(Queue));
	if (!queue){
		perror(MALLOC_ERROR);
		exit(EXIT_FAILURE); 
	} else{
		queue->begin = NULL;
		queue->end = NULL;
		queue->next = NULL;
		queue->size = ZERO;
	}
	return queue;
}

// Função que insere um novo elemento na queue.
Queue * push(Queue * queue, Node * newNode){
	Queue * new = (Queue *)malloc(sizeof(Queue)); 
	if (!new){
		perror(MALLOC_ERROR); 
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

// Função que remove o elemento da frente da queue, caso ela não esteja vazia. Caso a queue estiver vazia, desaloca-a da memória 
Queue * pop(Queue * queue){
	if (isEmpty(queue)){
		queue->end = NULL;
	} else{
		Queue *aux;
		aux = queue->begin;
		queue->begin = aux->next; 		 
		free(aux);
	}
	queue->size -= ONE;
	return queue; 
}

// Função que verifica se a queue está vazia
int isEmpty(Queue *queue){
	return (queue->begin == NULL)? ONE: ZERO; 
}

// Função que retorna o elemento da frente da queue
Node * front (Queue * queue){
	return isEmpty(queue)? NULL: queue->begin->node; 
}

// Função que retorna o elemento do fim da queue
Node * back (Queue * queue){
	return isEmpty(queue)? NULL: queue->end->node;  
}

// Função que retorna o tamanho da queue
int size(Queue * queue){
	return queue->size;
}

// Função que desaloca a queue da memória
void clearQueue(Queue * queue){
	if (queue)
		free(queue); 
	queue = NULL;
	
}
