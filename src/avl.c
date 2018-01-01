#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "queue.h"

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
typedef struct Cliente{
	int codigoCliente;
	int operacao;
	int valor;
	int saldo;
	int quantidadeOperacoes; 
} Cliente;

typedef struct Arvore {
	struct Cliente cliente;
	struct Arvore *direita;
	struct Arvore *esquerda;
	struct Arvore *pai;
	struct Arvore *raiz;
	int altura;
}No;

void definirArvore(No * novoNo){
	extern No arvore;
	arvore.raiz = inserirNo(&arvore, novoNo); 
	arvore.pai = NULL; 
}

void criarCliente (int codigoCliente, int operacao, int valor){
	Cliente * novoCliente = (Cliente *)malloc(sizeof(Cliente));
	if (!novoCliente){
		// perror() da biblioteca stdio.h para lançar na saída padrão o texto ERROR (da queue.h) junto com o erro especifico
		perror(ERROR);
		exit(TRUE);
	} else{
		novoCliente->codigoCliente = codigoCliente;
		novoCliente->operacao = operacao;
		novoCliente->valor = valor;
		novoCliente->saldo = ZERO;
		novoCliente->quantidadeOperacoes = ONE; 
		criarNo(novoCliente);
		free(novoCliente);
	}
}

// Aloca na memória um nó com os atributos do cliente 
void criarNo(Cliente * novoCliente){
	No * novoNo = (No *)malloc(sizeof(No));
	if (!novoNo){
		perror(ERROR);
		exit(TRUE);
	} else{
		novoNo->cliente = novoCliente;
		novoNo->direita = NULL;
		novoNo->esquerda = NULL;
		novoNo->pai = NULL;
		novoNo->altura = ZERO;
	}
}

// Função que insere o nó na arvore 
No * inserirNo(No * arvore, No * noAtual){
	if (arvore == NULL){
		return noAtual;
	}else{
		if (noAtual->cliente.codigoCliente > arvore->cliente.codigoCliente)
			noAtual->direita = inserirNo(arvore->direita, noAtual);
			
		if (noAtual->cliente.codigoCliente == arvore->cliente.codigoCliente)
			arvore = atualizarCliente(noAtual, arvore);
			
		if (noAtual->cliente.codigoCliente < arvore->cliente.codigoCliente)
			noAtual->esquerda = inserirNo(arvore->esquerda, noAtual);
	
		noAtual->altura = getAltura(noAtual);
		//abs(), da biblioteca <stdio.h>, retorna valor absoluto, i.e, módulo do número 
		if (abs(getAltura(noAtual->direita) - getAltura(noAtual->esquerda)) == UNBALANCED_TREE_LEFT)
			balanceamento(noAtual);
			
		return noAtual;
	}
}

// Função que atualiza os dados do cliente e retorna o no com os dados devidamente atualizados
No * atualizarCliente(No * noAtual, No * arvore){
	arvore->cliente.quantidadeOperacoes++; 
	//Depósito
	if (noAtual->cliente.operacao == ZERO)
		arvore->cliente.saldo += noAtual->cliente.valor;
	//Saque
	else
		arvore->cliente.saldo -= noAtual->cliente.valor;
	return arvore;
}

// Função que faz o balanceamento da arvore
// OBS: NAO SEI SE AS ROTAÇÕES SÃO ESSAS MESMAS PQ DO CRITERIO DE BALANCEAMENTO Q O PROF QUER TÁ INVERTIDO NOS ALGORITMO
No * balanceamento(No * x){
	if(getAltura(x->direita) - getAltura(x->esquerda) == UNBALANCED_TREE_RIGHT){
		No * y = x->esquerda;
		if(getAltura(y->direita) - getAltura(y->esquerda) == BALANCED_TREE_RIGHT){
			// Rotação dupla a esquerda 
		} else{
			// Rotação a esquerda 
		}
	}else if (getAltura(x->direita) - getAltura(x->esquerda) == UNBALANCED_TREE_LEFT){
		No * y = x->direita;
		if (getAltura(y->direita) - getAltura(y->esquerda) == BALANCED_TREE_RIGHT){
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
int getAltura(No * arvore){
	if (arvore == NULL)
		return -ONE; 
	arvore->altura = maximo(getAltura(arvore->esquerda), getAltura(arvore->direita)) + ONE;
	return arvore->altura;
}

// Função de busca da chave na arvore 
No * busca(No * arvore, int chave){
	if (arvore == NULL || chave == arvore->cliente.codigoCliente)
		return arvore;
	if (chave < arvore->cliente.codigoCliente)
		return busca(arvore->esquerda, chave);
	else 
		return busca(arvore->direita, chave);
	
}

void removerNo(No * noASerRemovido){
	// TODO
}

// Função que lista todos os nós da arvore em ordem crescente
void listarCrescente(No * raiz){
	listarCrescente(raiz->direita);
	printf("%d \n %d \n %d \n", raiz->cliente.codigoCliente, raiz->cliente.quantidadeOperacoes, raiz->cliente.saldo);
	listarCrescente(raiz->esquerda); 
}

// Função que lista todos os nós da arvore em ordem decrescente
void listarDecrescente(No * raiz){
	listarDecrescente(raiz->esquerda); 
	printf("%d \n %d \n %d \n", raiz->cliente.codigoCliente, raiz->cliente.quantidadeOperacoes, raiz->cliente.saldo);
	listarDecrescente(raiz->direita);
}

// Função que lista todos os nós da arvore em um determinado nível
int mostrarNivel(int nivel){
	if (!arvoreVazia()){
		if(isNotDefined())
			defineQueue();
		push(getQueue, getRaiz());
		for (register int i = 1; i<nivel; i++){
				if (front(getQueue)->esquerda != NULL) push(getQueue, front(getQueue)->esquerda); 
				if (front(getQueue)->direita != NULL) push(getQueue, front(getQueue)->direita); 
				pop(getQueue); 
		}
		while(!isEmpty(getQueue)){
			printf("%d \n", front(getQueue)->cliente.codigoCliente) 
			pop(getQueue());
		}
	} else{
		return FALSE;
	}
}

// Verifica se a arvore está vazia
int arvoreVazia(){
	return (getRaiz()->raiz == NULL)
}

// Retorna a raiz da arvore
No * getRaiz(){
	static No * external_root = &arvore;
	return external_root; 
}

// Retorna o novo nó
No * getNo(){
	return * novoNo;
}

