#include "Recebimentos.h"
#include "Recebimento.h"
#include "Cliente.h"
#include <stdio.h>
//TODO
Recebimento copiarRecebimento(Recebimento antigoRecebimento,Recebimento novoRecebimento)
{
	antigoRecebimento->numeroDocumento = novoRecebimento->numeroDocumento;
	antigoRecebimento->valorRecebimento = novoRecebimento->valorRecebimento;
	antigoRecebimento->dataEmissao = novoRecebimento->dataEmissao;
	antigoRecebimento->dataVencimento = novoRecebimento->dataVencimento;
	antigoRecebimento->codigoCliente = novoRecebimento->codigoCliente;	
	return(antigoRecebimento);
}
int proximoRecebimento(Cliente cliente)
{
	//Recebimentos eh uma lista global que contem em cada elemento uma struct do tipo Recebimento.
	//E o indice do recebimento corresponde a seu cliente e sua posicao na lista de recebimentos, ex:
	//cliente 2, recebimento 2, id = 2+2 = 4, esse recebimento estara na posicao 4 da lista Recebimentos.	
	int i,pos = 0;
	for(i=0;i<2;i++)
	{
		if(Recebimentos[cliente->codigoCliente+i].flag == 1) pos++;
	}
	return(pos);
}
int gerarNumDoc(Cliente cliente)
{
	return(cliente->codigoCliente+ProximoRecebimento(cliente));
}
Recebimento carregarRecebimento(unsigned int NumDoc)
{
	return(Recebimentos[NumDoc]);
}
