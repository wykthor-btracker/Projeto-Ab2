#ifndef RECEBIMENTO_H
#define RECEBIMENTO_H

#include "dependencias/stringHandling.h"

struct recebimento {
	unsigned int numeroDocumento;
	float valorRecebimento;
	char dataEmissao[11];
	char dataVencimento[11];
	unsigned int codigoCliente;
};

typedef struct recebimento* Recebimento;
typedef struct recebimento receb;

Recebimento novoRecebimento(unsigned int numeroDocumento,
		float valorRecebimento,
		String dataEmissao, String dataVencimento, 
		unsigned int codigoCliente);

int pegarNumDocumento(Recebimento recebimento);

float pegarValorRecebimento(Recebimento recebimento);

String pegarDataEmissao(Recebimento recebimento);

String pegarDataVencimento(Recebimento recebimento);

int pegarCodClienteRecebimento(Recebimento recebimento);

/*
Recebimento buscarRecebimentoPorCliente(Cliente listCliente, String nomeCliente);

Recebimento buscarRecebimentosporData(String dataInicio,String dataFinal);

int verificarQtdRecebimentos(Cliente listCliente, unsigned int codigoCliente);
*/

void destruirRecebimento(Recebimento recebimento);

#endif
