#include <stdlib.h>
#include <stdio.h>
#include "avl.h"

/* DE UMA OLHADA NO MATERIAL Q O PROF DISPONIBILIZOU NO CLASSROOM PQ LA TEM OS ALGORITMOS E TBM NO DESCRITIVO DO TRABALHO
 * OBS IMPORTANTISSIMA: CONSIDERE O FATOR DE BALANCEAMENTO SENDO (ALTURA DA DIREITA - ALTURA DA ESQUERDA) E CONSERTAR NOS ALGORITMO 
 * OUTRA OBS IMPORTANTE: PARENTE NÃO QUER VARIAVEIS GLOBAIS ENTAO TEMOS QUE TRABALHAR COM VARIAVEIS LOCAIS E PASSA-LA POR REFERENCIA SEJA PONTEIRO OU QUE FOR 
 * PRA FAZER (OLHA O TRELLO TBM):
 * Rotações todas 
 * Remoção de nó (OBS MT IMPORTANTE: Usar free(noAserRemovido) para desalocar da memoria perdemos pontos no trabalho passado pq nao usamos esse free)
 * Mostrar por nivel (usar o conceito de fila para mostrar por nivel NAO SEI SE É INTERESSANTE FAZER OUTRO ARQUIVO PRA UM TAD DE FILA)
 * Listar por ordem crescente (Esquerda-Raiz-Direita) ou decrescente (Direita-Raiz-Esquerda) 
 * Exibir relatorio pela ordem de remoção? (nao entendi mt bem essa ordem mas enfim)
 * Main 
 * NESSE TRABALHO NAO TEM MUITO ARQUIVO PRA DIVIDIR ENTAO VAI SER ASSIM: UM MEXE NO CODIGO DE CADA VEZ DPS A GENTE SE JUNTA PRA DAR UMA REVISADA GERAL
 * */

// Declaração das structs
struct Cliente{
	int codigoCliente;
	int operacao;
	int valor;
	int saldo;
};

typedef struct Arvore {
	struct Cliente cliente;
	struct Arvore *direita;
	struct Arvore *esquerda;
	struct Arvore *pai;
	struct Arvore *raiz;
	int altura;
} No;

void definirArvore(int codigoCliente, int operacao, int valor){
	No *arvore = (No *)malloc(1*sizeof(No)); 
	arvore.raiz = NULL;
	inserirNo(*arvore, criarNo(codigoCliente, operacao, valor); 
}
// Aloca na memória um nó com os atributos do cliente 
No criarNo(int codigoCliente, int operacao, int valor){
	struct Cliente novoCliente = (struct Cliente *)malloc(1 * sizeof(struct Cliente));
	novoCliente.codigoCliente = codigoCliente;
	novoCliente.operacao = operacao;
	novoCliente.valor = valor;
	novoCliente.saldo = 0;
	No novoNo = (No *)malloc(1 * sizeof(No);
	novoNo.cliente = novoCliente;
	novoNo.direita = NULL;
	novoNo.esquerda = NULL;
	novoNo.pai = NULL;
	novoNo.altura = 0;
	return novoNo;
}
// Função que insere o nó na arvore 
No inserirNo(No & arvore, No noAtual){
	if (arvore == NULL){
		return noAtual;
	}else{
		if (noAtual.cliente.codigoCliente > arvore.cliente.codigoCliente)
			noAtual.direita = inserirNo(arvore.direita, noAtual);
			
		if (noAtual.cliente.codigoCliente == arvore.cliente.codigoCliente)
			arvore = atualizarCliente(noAtual, arvore)
			
		if (noAtual.cliente.codigoCliente < arvore.cliente.codigoCliente)
			noAtual.esquerda = inserirNo(arvore.esquerda, noAtual);
			
		noAtual.altura = maximo(getAltura(noAtual.esquerda), getAltura(noAtual.direita)) + 1;
		//abs(), da biblioteca <stdio.h>, retorna valor absoluto, i.e, módulo do número 
		if (abs(getAltura(noAtual.direita) - getAltura(noAtual.esquerda)) == 2)
			balanceamento(noAtual);
			
		return noAtual;
	}
}

// Função que atualiza os dados do cliente e retorna o no com os dados devidamente atualizados
No atualizarCliente(No noAtual, No arvore){
	//Depósito
	if (noAtual.cliente.operacao == 0)
		arvore.cliente.saldo += noAtual.cliente.valor;
	//Saque
	else
		arvore.cliente.saldo -= noAtual.cliente.valor;
	return arvore;
}

// Função que faz o balanceamento da arvore
// OBS: NAO SEI SE AS ROTAÇÕES SÃO ESSAS MESMAS 
No balanceamento(No x){
	if(getAltura(x.direita) - getAltura(x.esquerda) == -2){
		No y = x.esquerda;
		if(getAltura(y.direita) - getAltura(y.esquerda) == -1){
			// Rotação dupla a esquerda 
		} else{
			// Rotação a esquerda 
		}
	}else if (getAltura(x.direita) - getAltura(x.esquerda) == 2){
		No y = x.direita;
		if (getAltura(y.direita) - getAltura(y.esquerda) == -1){
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
		return -1; 
	arvore.altura = maximo(getAltura(arvore.esquerda), getAltura(arvore.direita)) + 1;
	return arvore.altura;
}

// Função de busca da chave na arvore 
No busca(No & arvore, int chave){
	if (arvore == NULL || chave == arvore.cliente.codigoCliente)
		return arvore
	if chave < arvore.cliente.codigoCliente
		return busca(arvore.esquerda, chave);
	else 
		return busca(arvore.direita, chave);
	
}
