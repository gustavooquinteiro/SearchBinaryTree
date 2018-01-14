#include <stdlib.h>
#include <stdio.h>
#include "../lib/client.h"

// Declaração da struct
typedef struct cliente{
	long long int codigoCliente;
	int operacao;
	long long int valor;
	long long int saldo;
	long long int quantidadeOperacoes; 
} Client;

/* Função que aloca na memória um cliente com seus atributos
 * Caso não consiga alocar lança erro na saída padrão e sai do programa */
Client * criarCliente (int codigoCliente, int operacao, int valor){
	Client * novoCliente = (Client *)malloc(sizeof(Client));
	if (!novoCliente){
		perror(MALLOC_ERROR);
		exit(EXIT_FAILURE);
	} else{
		novoCliente->codigoCliente = codigoCliente;
		novoCliente->operacao = operacao;		
		novoCliente->valor = valor;
		novoCliente->saldo = ZERO;
		novoCliente->quantidadeOperacoes = ONE; 
		return novoCliente;
	}
}

/* Função que efetua a operação do cliente
 * Caso 0 será realizado um depósito
 * Caso 1 será realizado um saque */
Client * efetuarOperacao(Client * clienteAtual){
	if (clienteAtual->operacao == ZERO){
		clienteAtual->saldo += clienteAtual->valor;
	} else
		clienteAtual->saldo -= clienteAtual->valor;
	return clienteAtual;
}

// Função que atualiza os dados do cliente, efetuando a operação atual e atualizando a quantidade de operações
Client * atualizarCliente(Client * clienteAtual, Client * cliente){
	cliente = efetuarOperacao(clienteAtual); 
	cliente->quantidadeOperacoes++; 
	return cliente;
}

// Função que retorna o saldo do cliente
long long int getSaldoCliente(Client * cliente){
	return cliente->saldo;
}

// Função que retorna o código do cliente
long long int getClientCode(Client * client){
	return client->codigoCliente;
}

// Função que retorna a quantidade de operações do cliente
long long int getClientOperationsQuantity(Client * client){
	return client->quantidadeOperacoes;
}

// Função que retorna o valor a ser operado do cliente
long long int getClientValue(Client * client){
	return client->valor;
}

// Função que remove o cliente da memória
void removeClient(Client * client){
	free(client); 
}
