#include <stdlib.h>
#include <stdio.h>
#include "../lib/client.h"

typedef struct cliente{
	long long int codigoCliente;
	int operacao;
	long long int valor;
	long long int saldo;
	long long int quantidadeOperacoes; 
} Client;

Client * criarCliente (int codigoCliente, int operacao, int valor){
	Client * novoCliente = (Client *)malloc(sizeof(Client));
	if (!novoCliente){
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

Client * efetuarOperacao(Client * clienteAtual){
	//Depósito
	if (clienteAtual->operacao == ZERO){
		clienteAtual->saldo += clienteAtual->valor;
	//Saque
	} else
		clienteAtual->saldo -= clienteAtual->valor;
	return clienteAtual;
}

// Função que atualiza os dados do cliente e retorna o no com os dados devidamente atualizados
Client * atualizarCliente(Client * clienteAtual, Client * cliente){
	cliente = efetuarOperacao(clienteAtual); 
	cliente->quantidadeOperacoes++; 
	return cliente;
}

long long int getSaldoCliente(Client * cliente){
	return cliente->saldo;
}

long long int getClientCode(Client * client){
	return client->codigoCliente;
}

long long int getClientOperationsQuantity(Client * client){
	return client->quantidadeOperacoes;
}

long long int getClientValue(Client * client){
	return client->valor;
}
