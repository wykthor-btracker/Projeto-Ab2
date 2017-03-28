#include "Cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include "dependencias/stringHandling.h"
#include "ClienteExcecoes.h"
#include <stdio_ext.h>

#define DEBUG if(0)

//TO GET OBJECT FILE (Cliente.o)
//gcc -c Cliente.c

Cliente novoCliente(String nome, String endereco, 
	String telefone, unsigned int codigoCliente) {
	DEBUG printf("Inside novoCliente()\n");
	DEBUG printf("Creating new customer\n");
	Cliente cliente = (Cliente) malloc(sizeof(tamanhoCliente));

	if(nomeValido(nome)) 
		copyString(cliente->nome, nome);
	else {
		DEBUG printf("Given name is invalid: \'%s\'\n", nome);
		printf("Nome fornecido é inválido. Digite novamente: \n");
		scanf("%101[^\n]s", cliente->nome);
		__fpurge(stdin);
		DEBUG printf("New name: %s\n", cliente->nome);
	}
	if(telefoneValido(telefone))
		copyString(cliente->telefone, telefone);
	else {
		DEBUG printf("Given telefone is invalid: \'%s\'\n", telefone);
		printf("Telefone fornecido é inválido. Digite novamente: \n");
		scanf("%12[^\n]s", cliente->telefone);
		__fpurge(stdin);
		DEBUG printf("New telefone: %s\n", cliente->telefone);	
	}
	copyString(cliente->endereco, endereco);
	cliente->codigoCliente = codigoCliente;
	return cliente;
}

String pegarNome(Cliente cliente) {
	return cliente->nome;
}

String pegarEndereco(Cliente cliente) {
	return cliente->endereco;
}

String pegarTelefone(Cliente cliente) {
	return cliente->telefone;
}

int pegarCodigoCliente(Cliente cliente) {
	return cliente->codigoCliente;
}

void mudarNome(Cliente cliente, String novoNome) {
	if(!nomeValido(novoNome)) {
		printf("Nome fornecido é inválido. Digite novamente: \n");
		scanf("%101[^\n]s", cliente->nome);
	} else {
		copyString(cliente->nome, novoNome);
	}
}

void mudarEndereco(Cliente cliente, String novoEndereco) {
	copyString(cliente->endereco, novoEndereco);
}

void mudarTelefone(Cliente cliente, String novoTelefone) {
	if(!telefoneValido(novoTelefone)) {
		printf("Telefone fornecido é inválido. Digite novamente: \n");
		scanf("%12[^\n]s", cliente->telefone);
	} else {
		copyString(cliente->telefone, novoTelefone);	
	}
}

void mudarCodigoCliente(Cliente cliente, 
					unsigned int novoCodigo) {
	cliente->codigoCliente = novoCodigo;
}

int pegarContador(Cliente cliente) {
	return cliente->contador;
}

void mudarContador(Cliente cliente, int novoContador) {
	cliente->contador = novoContador;
}

void destruirCliente(Cliente cliente) {
	free(cliente);
}
