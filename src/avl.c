#include <stdio.h>
#include <stdlib.h>
#include "../lib/avl.h"
#include "../lib/queue.h"

/* DE UMA OLHADA NO MATERIAL Q O PROF DISPONIBILIZOU NO CLASSROOM PQ LA TEM OS ALGORITMOS E TBM NO DESCRITIVO DO TRABALHO
 * OBS IMPORTANTISSIMA: CONSIDERE O FATOR DE BALANCEAMENTO SENDO (ALTURA DA DIREITA - ALTURA DA ESQUERDA) E CONSERTAR NOS ALGORITMO 
 * OUTRA OBS IMPORTANTE: PARENTE NÃO QUER VARIAVEIS GLOBAIS ENTAO TEMOS QUE TRABALHAR COM VARIAVEIS LOCAIS E PASSA-LA POR REFERENCIA DE PONTEIRO 
 * PRA FAZER (OLHA O TRELLO TBM):
 * Rotações todas 
 * Remoção de nó (OBS MT IMPORTANTE: Usar free(noAserRemovido) para desalocar da memoria perdemos pontos no trabalho passado pq nao usamos esse free)
 * Mostrar por nivel (TA MEIO FEITO OLHA O queue.c TEM MEU AVAL PRA MEXER LÁ)
 * Exibir relatorio pela ordem de remoção? (nao entendi mt bem essa ordem mas enfim)
 * NESSE TRABALHO NAO TEM MUITO ARQUIVO PRA DIVIDIR ENTAO VAI SER ASSIM: UM MEXE NO CODIGO DE CADA VEZ DPS A GENTE SE JUNTA PRA DAR UMA REVISADA GERAL
 * */
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
	struct no *right;
	struct no *left;
	struct no *dad;
	int height;
	int balanceFactor; 
} Node;

typedef struct tree{
	Node * root;
	int treeHeight;
} AVLtree; 

AVLtree * definirArvore(){
	AVLtree * arvore = (AVLtree *)malloc(sizeof(AVLtree));
	if (!arvore){
		// perror() da stdio.h para lançar na saída padrão o texto ERROR (da queue.h) junto com o erro especifico
		perror(ERROR);
		//exit() da stdlib.h para interromper a execução do programa com o código de falha
		exit(EXIT_FAILURE);
	}
	
	// Define arvore com altura 0, i.e arvore vazia
	arvore->treeHeight = getAltura(arvore->root) + ONE;
	return arvore;
}

Node * definirRaiz(AVLtree * arvore, Node * novoNo){
	arvore->root = inserirNo(isTreeEmpty(arvore), novoNo); 
	arvore->treeHeight = getAltura(arvore->root) + ONE;	
	return arvore->root;
}

Node * criarCliente (int codigoCliente, int operacao, int valor){
	Client * novoCliente = (Client *)malloc(sizeof(Client));
	if (!novoCliente){
		perror(ERROR);
		exit(EXIT_FAILURE);
	} else{
		novoCliente->codigoCliente = codigoCliente;
		novoCliente->operacao = operacao;		
		novoCliente->valor = valor;
		novoCliente->saldo = ZERO;
		novoCliente->quantidadeOperacoes = ONE; 
		return criarNo(novoCliente);
	}
}

// Aloca na memória um nó com os atributos do cliente 
Node * criarNo(Client * novoCliente){
	Node * novoNo = (Node *)malloc(sizeof(Node));
	if (!novoNo){
		perror(ERROR);
		exit(EXIT_FAILURE);
	} else{
		novoNo->client = *(novoCliente);
		novoNo->right = NULL;
		novoNo->left = NULL;
		novoNo->dad = NULL;
	}
	return novoNo;
}

// Função que insere o nó na arvore 
Node * inserirNo(Node * raiz, Node * noAtual){
	
	if (raiz){
		if (noAtual->client.codigoCliente > raiz->client.codigoCliente){
			raiz->right = inserirNo(raiz->right, noAtual);
			raiz->right->dad = raiz;
		}
			
		if (noAtual->client.codigoCliente == raiz->client.codigoCliente)
			raiz = atualizarCliente(noAtual, raiz);
			
		if (noAtual->client.codigoCliente < raiz->client.codigoCliente){
			raiz->left = inserirNo(raiz->left, noAtual);
		}
		raiz->height = getAltura(raiz);
		raiz->balanceFactor = getAltura(raiz->right) - getAltura(raiz->left); 
		//abs(numero), da stdio.h, retorna valor absoluto, i.e, módulo do número 
		if (abs(raiz->balanceFactor) == UNBALANCED_TREE_MODULE)
			raiz = balanceamento(raiz);		
		
	}else{
		raiz = noAtual; 
		raiz->balanceFactor = ZERO;
	}
	return raiz;
}

// Função que atualiza os dados do cliente e retorna o no com os dados devidamente atualizados
Node * atualizarCliente(Node * noAtual, Node * arvore){
	//Depósito
	if (noAtual->client.operacao == ZERO){
		arvore->client.saldo += noAtual->client.valor;
	//Saque
	} else
		arvore->client.saldo -= noAtual->client.valor;
	arvore->client.quantidadeOperacoes++; 
	return arvore;
}

// Função que faz o balanceamento da arvore
// OBS: NAO SEI SE AS ROTAÇÕES SÃO ESSAS MESMAS PQ DO CRITERIO DE BALANCEAMENTO Q O PROF QUER TÁ INVERTIDO NOS ALGORITMO
Node * balanceamento(Node * x){
	if(x->balanceFactor == UNBALANCED_TREE_RIGHT){
		Node * y = x->left;
		if(y->balanceFactor == BALANCED_TREE_LEFT){
			// Rotação dupla a esquerda 
		} else{
			// Rotação a esquerda 
		}
	}else if (x->balanceFactor == UNBALANCED_TREE_LEFT){
		Node * y = x->right;
		if (y->balanceFactor == BALANCED_TREE_LEFT){
			// Rotação dupla a direita
		}else{
			// Rotação a direita
		}	
	}
	return x; 
}

/* Função que retorna o maior valor entre os dois parametros recebidos 
 * Mesma coisa q 
 * if (esquerda > direita)
 * 	return esquerda
 * else
 * 	return direita
 * */
int maximo(int esquerda, int direita){
	return esquerda > direita ? esquerda: direita;
}

// Função que retorna a altura de determinado no da arvore
int getAltura(Node * node){
	if (!node)
		return MINUS_ONE; 
	node->height = maximo(getAltura(node->left), getAltura(node->right)) + ONE;
	return node->height;
}

// Função de busca da chave na arvore 
Node * busca(Node * arvore, int chave){
	if (!arvore || chave == arvore->client.codigoCliente)
		return arvore;
	if (chave < arvore->client.codigoCliente){
		return busca(arvore->left, chave);
	} else 
		return busca(arvore->right, chave);
}

/*void removerNo(Node * arvore, int chave){
	// TODO
}*/

// Função que lista todos os nós da arvore em ordem crescente
Node * listarCrescente(Node * raiz){
	if (!raiz->left) listarCrescente(raiz->left);
	printf("%d\n %d\n %d\n", raiz->client.codigoCliente, raiz->client.quantidadeOperacoes, raiz->client.saldo);
	if (!raiz->right) listarCrescente(raiz->right); 
	return raiz; 
}

// Função que lista todos os nós da arvore em ordem decrescente
Node * listarDecrescente(Node * raiz){
	if (!raiz->right) listarDecrescente(raiz->right); 
	printf("%d \n %d\n %d\n", raiz->client.codigoCliente, raiz->client.quantidadeOperacoes, raiz->client.saldo);
	if (!raiz->left) listarDecrescente(raiz->left);
	return raiz;
}

// Função que lista todos os nós da arvore em um determinado nível
void mostrarNivel(int nivel, AVLtree * arvore){
	Node * raiz = getRaiz(arvore);
	if (raiz){
		Queue * fila = defineQueue();	
		fila = push(fila, raiz);
		for (register int iterator = ZERO; iterator < nivel; iterator++){
				if (isEmpty(fila)) break;
				// Se existe filho a esquerda coloca na fila 
				if (front(fila)->left) push(fila, front(fila)->left); 
				// Se existe filho a direita coloca na fila 
				if (front(fila)->right) push(fila, front(fila)->right); 
				pop(fila); 
		}
		while(!isEmpty(fila)){
			printf("%d \n", front(fila)->client.codigoCliente); 
			pop(fila);
		}
	}
} 

Node * isTreeEmpty(AVLtree * arvore){
	if (arvore->treeHeight == ZERO) 
		return NULL;	
	return arvore->root;
}

Node * isRootDefined(AVLtree * arvore){
	if (!arvore->root)
		return NULL;
	return arvore->root;
}

Node * getRaiz(AVLtree * arvore){
	return isRootDefined(arvore); 
}
