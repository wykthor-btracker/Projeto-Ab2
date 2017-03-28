#ifndef RECEBIMENTO_H
#define RECEBIMENTO_H

#include "dependencias/stringHandling.h"
#include "dependencias/data.h"

struct recebimento {
	unsigned int numeroDocumento;
	float valorRecebimento;
	Data dataEmissao;
	Data dataVencimento;
	unsigned int codigoCliente;
	int flag;
};

typedef struct recebimento* Recebimento;
typedef struct recebimento receb;

Recebimento novoRecebimento(unsigned int numeroDocumento,
		float valorRecebimento,
		Data dataEmissao, Data dataVencimento, 
		unsigned int codigoCliente);

int pegarNumDocumento(Recebimento recebimento);

float pegarValorRecebimento(Recebimento recebimento);

Data pegarDataEmissao(Recebimento recebimento);

Data pegarDataVencimento(Recebimento recebimento);

int pegarCodClienteRecebimento(Recebimento recebimento);

void mudarDataVencimento(Recebimento recebimento,Data dataVencimento);

void mudarDataEmissao(Recebimento recebimento, Data dataEmissao);

void mudarValorRecebimento(Recebimento recebimento, float valorRecebimento);

void destruirRecebimento(Recebimento recebimento);

#endif
