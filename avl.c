#include <stdlib.h>
#include "avl.h"

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

No inserirNo(No & arvore, No noAtual){
	if (arvore == NULL){
		return noAtual;
	}else{
		if (noAtual.cliente.codigoCliente > arvore.cliente.codigoCliente)
			noAtual.direita = inserirNo(arvore.direita, noAtual);
			
		if (noAtual.cliente.codigoCliente == arvore.cliente.codigoCliente)
			noAtual = atualizarCliente(noAtual, arvore)
			
		if (noAtual.cliente.codigoCliente < arvore.cliente.codigoCliente)
			noAtual.esquerda = inserirNo(arvore.esquerda, noAtual);
			
		noAtual.altura = maximo(getAltura(noAtual.esquerda), getAltura(noAtual.direita)) + 1;
		if (abs(getAltura(noAtual.direita) - getAltura(noAtual.esquerda)) == 2)
			balanceamento(noAtual);
			
		return noAtual;
	}
}

No atualizarCliente(No noAtual, No arvore){
	if (noAtual.cliente.operacao == 0)
		arvore.cliente.saldo += noAtual.cliente.valor;
	else
		arvore.cliente.saldo -= noAtual.cliente.valor;
	return arvore;
}

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

int maximo(int esquerda, int direita){
	return esquerda > direita ? esquerda: direita;
}

int getAltura(No * arvore){
	if (arvore == NULL)
		return -1; 
	arvore.altura = maximo(getAltura(arvore.esquerda), getAltura(arvore.direita)) + 1;
	return arvore.altura;
}

No busca(No & arvore, int chave){
	if (arvore == NULL || chave == arvore.cliente.codigoCliente)
		return arvore
	if chave < arvore.cliente.codigoCliente
		return busca(arvore.esquerda, chave);
	else 
		return busca(arvore.direita, chave);
	
}

// Remoção de nó 
