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

Client * efetuarOperacao(Client * clienteAtual){
	if (clienteAtual->operacao == ZERO){
		clienteAtual->saldo += clienteAtual->valor;
	} else
		clienteAtual->saldo -= clienteAtual->valor;
	return clienteAtual;
}

Client * atualizarCliente(Client * clienteAtual, Client * cliente){
	if (clienteAtual->operacao == ZERO){
		cliente->saldo += clienteAtual->valor;
	} else
		cliente->saldo -= clienteAtual->valor;
	cliente->quantidadeOperacoes++;
    removeClient(clienteAtual);
	return cliente;
}


long long int getSaldoCliente(Client * cliente){
	return cliente->saldo;
}

long long int getClientCode(Client * client){
	if(client)
        return client->codigoCliente;
	return -1;
}

long long int getClientOperation(Client* client) {
	if(client)
        return client->operacao;
	return -1;
}

long long int getClientOperationsQuantity(Client * client){
	return client->quantidadeOperacoes;
}

long long int getClientValue(Client * client){
	return client->valor;
}

void alterarClient(Client* client, long long clientCode, long long value, long long operation, long long saldo, long long clientOperationsQuantity) {
	if(client) {
		client->codigoCliente = clientCode;
		client->valor = value;
		client->saldo = saldo;
		client->operacao = operation;
		client->quantidadeOperacoes = clientOperationsQuantity;
	}
}

void removeClient(Client * client){
	if (client)
		free(client);
}
