#include "../lib/queue.h"

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

Queue * pop(Queue * queue){
	if (isEmpty(queue)){
		queue->end = NULL;
	} else{
		Queue *aux = queue->begin;
		queue->begin = aux->next; 		 
		free(aux);
	}
	queue->size -= ONE;
	return queue; 
}

int isEmpty(Queue *queue){
	return (queue->begin == NULL)? ONE: ZERO; 
}

Node * front (Queue * queue){
	return isEmpty(queue)? NULL: queue->begin->node; 
}

Node * back (Queue * queue){
	return isEmpty(queue)? NULL: queue->end->node;  
}

int size(Queue * queue){
	return queue->size;
}

void clearQueue(Queue * queue){
	if (queue)
		free(queue); 
	queue = NULL;
	
}
