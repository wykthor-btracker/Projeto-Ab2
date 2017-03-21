#ifndef RECEBIMENTO_H
#define RECEBIMENTO_H

#include "dependencias/stringHandling.h"

struct recebimento {
	unsigned int numeroDocumento;
	unsigned float valorRecebimento;
	char dataEmissao[11];
	char dataVencimento[11];
	unsigned int codigoCliente;
};

typedef struct recebimento* Recebimento;

Recebimento novoRecebimento(unsigned int numeroDocumento,
		unsigned float valorRecebimento,
		String dataEmissao, String dataVencimento, 
		unsigned int codigoCliente);

#endif
