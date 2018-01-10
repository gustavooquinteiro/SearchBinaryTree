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

typedef struct tree{
	Client client;
	struct tree *right;
	struct tree *left;
	struct tree *dad;
	int height;
} Node;

extern Node * raiz; 

void definirArvore(Node * novoNo){
	raiz = (Node *)malloc(sizeof(Node));
	if (!raiz){
		perror(ERROR);
		exit(EXIT_FAILURE);	
	} 
	raiz = inserirNo(raiz, novoNo); 
	raiz->dad = NULL; 
}

Node * criarCliente (int codigoCliente, int operacao, int valor){
	Client * novoCliente = (Client *)malloc(sizeof(Client));
	if (!novoCliente){
		// perror() da biblioteca stdio.h para lançar na saída padrão o texto ERROR (da queue.h) junto com o erro especifico
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
		novoNo->height = ZERO;
	}
	return novoNo;
}

// Função que insere o nó na arvore 
Node * inserirNo(Node * arvore, Node * noAtual){
	if (!arvore){
		return noAtual;
	}else{
		if (noAtual->client.codigoCliente > arvore->client.codigoCliente)
			noAtual->right = inserirNo(arvore->right, noAtual);
			
		if (noAtual->client.codigoCliente == arvore->client.codigoCliente)
			arvore = atualizarCliente(noAtual, arvore);
			
		if (noAtual->client.codigoCliente < arvore->client.codigoCliente)
			noAtual->left = inserirNo(arvore->left, noAtual);
	
		noAtual->height = getAltura(noAtual);
		//abs(), da biblioteca <stdio.h>, retorna valor absoluto, i.e, módulo do número 
		if (abs(getAltura(noAtual->right) - getAltura(noAtual->left)) == TWO)
			balanceamento(noAtual);
			
		return noAtual;
	}
}

// Função que atualiza os dados do cliente e retorna o Node com os dados devidamente atualizados
Node * atualizarCliente(Node * noAtual, Node * arvore){
	arvore->client.quantidadeOperacoes++; 
	//Depósito
	if (noAtual->client.operacao == ZERO){
		arvore->client.saldo += noAtual->client.valor;
	//Saque
	} else
		arvore->client.saldo -= noAtual->client.valor;
	return arvore;
}

// Função que faz o balanceamento da arvore
// OBS: NAO SEI SE AS ROTAÇÕES SÃO ESSAS MESMAS PQ DO CRITERIO DE BALANCEAMENTO Q O PROF QUER TÁ INVERTIDO NOS ALGORITMO
Node * balanceamento(Node * x){
	if(getAltura(x->right) - getAltura(x->left) == UNBALANCED_TREE_RIGHT){
		Node * y = x->left;
		if(getAltura(y->right) - getAltura(y->left) == BALANCED_TREE_RIGHT){
			// Rotação dupla a esquerda 
		} else{
			// Rotação a esquerda 
		}
	}else if (getAltura(x->right) - getAltura(x->left) == UNBALANCED_TREE_LEFT){
		Node * y = x->right;
		if (getAltura(y->right) - getAltura(y->left) == BALANCED_TREE_RIGHT){
			// Rotação dupla a right
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
int getAltura(Node * arvore){
	if (!arvore)
		return -ONE; 
	arvore->height = maximo(getAltura(arvore->left), getAltura(arvore->right)) + ONE;
	return arvore->height;
}

// Função de busca da chave na arvore 
Node * busca(Node * arvore, int chave){
	if (!arvore || chave == arvore->client.codigoCliente)
		return arvore;
	if (chave < arvore->client.codigoCliente)
		return busca(arvore->left, chave);
	else 
		return busca(arvore->right, chave);
	
}

/*void removerNo(Node * arvore, int chave){
	// TODO
}*/

// Função que lista todos os nós da arvore em ordem crescente
void listarCrescente(Node * raiz){
	listarCrescente(raiz->left);
	printf("%d \n %d \n %d \n", raiz->client.codigoCliente, raiz->client.quantidadeOperacoes, raiz->client.saldo);
	listarCrescente(raiz->right); 
}

// Função que lista todos os nós da arvore em ordem decrescente
void listarDecrescente(Node * raiz){
	listarDecrescente(raiz->right); 
	printf("%d \n %d \n %d \n", raiz->client.codigoCliente, raiz->client.quantidadeOperacoes, raiz->client.saldo);
	listarDecrescente(raiz->left);
}

// Função que lista todos os nós da arvore em um determinado nível
void mostrarNivel(int nivel){
	if (!arvoreVazia()){
		// Se eu não conseguir definir uma queue (retorno de defineQueue == NULL) dê erro de alocação e saia
		Queue * fila = defineQueue();
		if(!fila){
			perror(ERROR);
			exit(EXIT_FAILURE);
		}
		push(fila, getRaiz());
		for (register int i = ONE; i < nivel; i++){
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

// Verifica se a arvore está vazia
Node * arvoreVazia(){
	return getRaiz();  
}

Node * getRaiz(){
	return raiz;
}
