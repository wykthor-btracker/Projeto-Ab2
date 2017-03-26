#ifndef CLIENTE_H
#define CLIENTE_H

#include "dependencias/stringHandling.h"

struct cliente {
	char nome[101];
	char endereco[201];
	char telefone[12];
	unsigned int codigoCliente;
};

typedef struct cliente* Cliente;

Cliente novoCliente(String nome, String endereco, 
	String telefone, unsigned int codigoCliente);

#endif
