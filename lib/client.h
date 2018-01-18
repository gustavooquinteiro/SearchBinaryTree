#ifndef CLIENT_H
#define CLIENT_H

// Definição de constantes para legibilizar código
#define ZERO 0
#define ONE 1
#define MALLOC_ERROR "Dynamic allocation failed"

// Assinaturas das funções e structs
typedef struct cliente Client;

Client * criarCliente (int codigoCliente, int operacao, int valor);
Client * efetuarOperacao(Client * no);
Client * atualizarCliente(Client * noAtual, Client * arvore);
long long int getSaldoCliente(Client * cliente);
long long int getClientCode(Client * client);
long long int getClientOperationsQuantity(Client * client);
long long int getClientValue(Client * client);
void removeClient(Client * client);


#endif
