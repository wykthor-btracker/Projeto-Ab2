#include "Cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include "dependencias/stringHandling.h"

//TO GET OBJECT FILE (Cliente.o)
//gcc -c Cliente.c

Cliente novoCliente(String nome, String endereco, 
	String telefone, unsigned int codigoCliente) {
	Cliente cliente = (Cliente) malloc(sizeof(tamanhoCliente));
	copyString(cliente->nome, nome);
	copyString(cliente->endereco, endereco);
	copyString(cliente->telefone, telefone);
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
	copyString(cliente->nome, novoNome);
}

void mudarEndereco(Cliente cliente, String novoEndereco) {
	copyString(cliente->endereco, novoEndereco);
}

void mudarTelefone(Cliente cliente, String novoTelefone) {
	copyString(cliente->telefone, novoTelefone);
}

void mudarCodigoCliente(Cliente cliente, 
					unsigned int novoCodigo) {
	cliente->codigoCliente = novoCodigo;
}

void destruirCliente(Cliente cliente) {
	free(cliente);
}
