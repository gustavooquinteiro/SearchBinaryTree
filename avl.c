#include <stdlib.h>
#include <stdio.h>

struct Cliente{
	int codigoCliente;
	int operacao;
	int valor;
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
	No novoNo = (No *)malloc(1 * sizeof(No);
	novoNo.cliente = novoCliente;
	novoNo.direita = NULL;
	novoNo.esquerda = NULL;
	novoNo.pai = NULL;
	novoNo.altura = 0;
	return novoNo;
}

void inserirNo(No & arvore, No noAtual){
	if (arvoreVazia()){
		arvore.raiz = noAtual;
	} else{
		balanceamento(No & arvore);
		if (noAtual.cliente.codigoCliente > arvore.cliente.codigoCliente)
			inserirNo(arvore.direita, noAtual);
		if (noAtual.cliente.codigoCliente == arvore.cliente.codigoCliente)
			atualizarCliente(noAtual, arvore)
		if (noAtual.cliente.codigoCliente < arvore.cliente.codigoCliente)
			inserirNo(arvore.esquerda, noAtual);
	}
}

int balanceamento(No * arvore){
	int coeficienteDeBalanceamento = getAltura(arvore.direita) - getAltura(arvore.esquerda); 
	if(abs(coeficienteDeBalanceamento) == 1){
		
	}else{
		
	}
}

int maximo(int esquerda, int direita){
	return esquerda > direita ? esquerda: direita;
}

int getAltura(No * arvore){
	int esquerda, direita;
	if (arvore == NULL)
		return esquerda + 1; 
	if(arvore.esquerda != NULL)
		return esquerda += getAltura(arvore.esquerda);
	if(arvore.direita != NULL)
		return direita += getAltura(arvore.direita);
}
