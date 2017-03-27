#include "Recebimento.h"
#include "dependencias/stringHandling.h"
#include <stdio.h>
#include <stdlib.h>

//to get object file (Recebimento.o)
//gcc -c Recebimento.c

Recebimento novoRecebimento(unsigned int numeroDocumento,
		float valorRecebimento,
		String dataEmissao, String dataVencimento, 
		unsigned int codigoCliente) {

	Recebimento recebimento = (Recebimento) malloc(sizeof(receb));
	recebimento->numeroDocumento = numeroDocumento;
	recebimento->valorRecebimento = valorRecebimento;
	copyString(recebimento->dataEmissao,dataEmissao);
	copyString(recebimento->dataVencimento,dataVencimento);
	recebimento->codigoCliente = codigoCliente;

	return recebimento;
}

int pegarNumDocumento(Recebimento recebimento){
	return recebimento->numeroDocumento;
}

float pegarValorRecebimento(Recebimento recebimento){
	return recebimento->valorRecebimento;
}

String pegarDataEmissao(Recebimento recebimento){
	return recebimento->dataEmissao;
}

String pegarDataVencimento(Recebimento recebimento){
	return recebimento->dataVencimento;
}

int pegarCodClienteRecebimento(Recebimento recebimento){
	return recebimento->codigoCliente;
}

/*
Recebimento buscarRecebimentoPorCliente(Cliente listCliente,String nomeCliente){ 

}

Recebimento buscarRecebimentosporData(String dataInicio,String dataFinal){
	
}

int verificarQtdRecebimentos(Cliente listCliente, unsigned int codigoCliente){
	int count = 0;

	while(listCliente->next != NULL){
		if(isEqual(listCliente->cliente->codigoCliente,codigoCliente))
			count++;

		listCliente = listCliente->next;
	}

	return count;
}
*/

void destruirRecebimento(Recebimento recebimento){
	free(recebimento);
}

