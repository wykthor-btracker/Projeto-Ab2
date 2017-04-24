#include "Recebimento.h"
#include "RecebimentoExcecoes.h"
#include "dependencias/stringHandling.h"
#include "dependencias/data.h"
#include <stdio.h>
#include <stdlib.h>

//to get object file (Recebimento.o)
//gcc -c Recebimento.c

Recebimento novoRecebimento(unsigned int numeroDocumento,
		float valorRecebimento,
		Data dataEmissao, Data dataVencimento, 
		unsigned int codigoCliente) {

	Recebimento recebimento = (Recebimento) malloc(sizeof(receb));
	recebimento->numeroDocumento = numeroDocumento;
	recebimento->valorRecebimento = valorRecebimento;

	while(!validaData(dataEmissao)){
		printf("Formato da data de emissão inválido, informe uma data no formato: dd/mm/yyyy\nDigite uma nova data de emissão:");
		scanf(" %d/%d/%d",&recebimento->dataEmissao.dia,&recebimento->dataEmissao.mes,&recebimento->dataEmissao.ano);
	}

	while(!validaData(dataVencimento)){
		printf("Formato da data de vencimento inválido, informe uma data no formato dd/mm/yyyy\nDigite uma nova data de vencimento:");
		scanf(" %d/%d/%d",&recebimento->dataVencimento.dia,&recebimento->dataVencimento.mes,&recebimento->dataVencimento.ano);
	}
	
	while(!validaData(dataVencimento) && !validarDataRecebimento(dataEmissao,dataVencimento) ){
		printf("A data de vencimento é menor do que a data de emissão, informe uma nova data de vencimento no formato dd/mm/yyyy:\n");
		scanf(" %d/%d/%d",&recebimento->dataVencimento.dia,&recebimento->dataVencimento.mes,&recebimento->dataVencimento.ano);
	}

	recebimento->dataEmissao = dataEmissao;
	recebimento->dataVencimento = dataVencimento;
	recebimento->codigoCliente = codigoCliente;
	
	recebimento->flag = 0;

	return recebimento;
}

int pegarNumDocumento(Recebimento recebimento){
	return recebimento->numeroDocumento;
}

float pegarValorRecebimento(Recebimento recebimento){
	return recebimento->valorRecebimento;
}

Data pegarDataEmissao(Recebimento recebimento){
	return recebimento->dataEmissao;
}

Data pegarDataVencimento(Recebimento recebimento){
	return recebimento->dataVencimento;
}

int pegarCodClienteRecebimento(Recebimento recebimento){
	return recebimento->codigoCliente;
}

void mudarDataVencimento(Recebimento recebimento,Data dataVencimento){
	recebimento->dataVencimento = dataVencimento;
}

void mudarDataEmissao(Recebimento recebimento, Data dataEmissao){
	recebimento->dataEmissao = dataEmissao;
}

void mudarValorRecebimento(Recebimento recebimento, float valorRecebimento){
	recebimento->valorRecebimento = valorRecebimento;
}

void destruirRecebimento(Recebimento recebimento){
	free(recebimento);
}

