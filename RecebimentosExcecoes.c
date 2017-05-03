#include "RecebimentosExcecoes.h"
#include "dependencias/stringHandling.h"
#include <stdio.h>
#include <stdlib.h>
#include "Cliente.h"
#include "Recebimentos.h"
#ifndef	DEBUG
#define DEBUG if(0)
#endif

int codigoClienteInvalido(const int codigoCliente) {
	return codigoCliente < 0;
}

int codigoRecebimentoInvalido(const int codigoRecebimento) {
	return codigoRecebimento < 0;
}
