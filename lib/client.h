#include <stdlib.h>
#include <stdio.h>
#ifndef CLIENT_H
#define CLIENT_H

// Definição de constantes 
#define ZERO 0
#define ONE 1
#define MALLOC_ERROR "Dynamic allocation failed"

// Assinaturas da struct do cliente
typedef struct cliente Client;

// Função que aloca na memória um cliente com seus atributos
Client * criarCliente (int codigoCliente, int operacao, int valor);

// Função que efetua a operação do cliente
Client * efetuarOperacao(Client * no);

// Função que atualiza os dados do cliente, efetuando a operação atual e atualizando a quantidade de operações
Client * atualizarCliente(Client * noAtual, Client * arvore);

// Função que retorna o saldo do cliente
long long int getSaldoCliente(Client * cliente);

// Função que retorna o código do cliente
long long int getClientCode(Client * client);

// Função que retorna a quantidade de operações do cliente
long long int getClientOperationsQuantity(Client * client);

// Função que retorna o valor a ser operado do cliente
long long int getClientValue(Client * client);

// Função que retorna a operação do cliente
long long int getClientOperation(Client* client);

// Função que realiza a cópia do cliente
void alterarClient(Client* client, long long clientCode, long long value, long long operation, long long saldo, long long clientOperationsQuantity);

// Função que remove o cliente da memória
void removeClient(Client * client);


#endif
