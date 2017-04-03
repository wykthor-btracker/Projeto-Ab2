#include "Recebimentos.h"
#include "Recebimento.h"
#include "RecebimentoExcecoes.h"
#include "Cliente.h"
#include <stdio.h>
#include <stdlib.h>
//TODO
Recebimento *listarRecebimentos(int size, Recebimento *lista)
{
	FILE *fw;
	int i;
	lista = malloc(sizeof(receb)*size);
	for(i=0;i<size;i++) lista[i] = malloc(sizeof(receb));
	if((fw = fopen("recebimentos.dat","r+"))==NULL) printf("SHIT\n");
	i = 0;
	while(fscanf(fw,"%u %f %d/%d/%d %d/%d/%d %u %d",
		&lista[i]->numeroDocumento,
		&lista[i]->valorRecebimento,
		&lista[i]->dataEmissao.dia,
		&lista[i]->dataEmissao.mes,
		&lista[i]->dataEmissao.ano,
		&lista[i]->dataVencimento.dia,
		&lista[i]->dataVencimento.mes,
		&lista[i]->dataVencimento.ano,
		&lista[i]->codigoCliente,
		&lista[i]->flag)!=EOF) i++;
	fclose(fw);
	return(lista);
}	
Recebimento recebimentosLista[30];//Solucao temporaria pra falta de uma lista global de structs

void carregarRecebimentoPorCliente(Cliente cliente,Recebimento *recebimentos)
{
	int i;
	for(i=0;i<2;i++)
	{
		copiarRecebimento(carregarRecebimento((cliente->codigoCliente) + i),recebimentos[i]);
	}
}	

void carregarRecebimentosPorData(Data inicio,Data fim,Recebimento *recebimentosLista)
{
		//Alocar espaco suficiente pra lista, comparar datas dadas como parametros
		//e retornar uma lista contendo todos os recebimentos requisitados.
}
Recebimento copiarRecebimento(Recebimento antigoRecebimento,Recebimento novoRecebimento)
{
	antigoRecebimento->numeroDocumento = novoRecebimento->numeroDocumento;
	antigoRecebimento->valorRecebimento = novoRecebimento->valorRecebimento;
	antigoRecebimento->dataEmissao = novoRecebimento->dataEmissao;
	antigoRecebimento->dataVencimento = novoRecebimento->dataVencimento;
	antigoRecebimento->codigoCliente = novoRecebimento->codigoCliente;
	antigoRecebimento->flag = novoRecebimento->flag;
	return(antigoRecebimento);
}

int salvarRecebimento(Recebimento recebimento,Cliente cliente)
{
	 int id = registroDisponivel(cliente);
	 if(id == -1) return(0);
	 recebimentosLista[id] = copiarRecebimento(recebimentosLista[id],recebimento);
	 recebimentosLista[id]->flag = 1;
	 return 1;
}

int proximoRecebimento(Cliente cliente)
{
	//Recebimentos eh uma lista global que contem em cada elemento uma struct do tipo Recebimento.
	//E o indice do recebimento corresponde a seu cliente e sua posicao na lista de recebimentos, ex:
	//cliente 2, recebimento 2, id = 2+2 = 4, esse recebimento estara na posicao 4 da lista Recebimentos.	
	int i,pos = 0;
	for(i=0;i<2;i++)
	{
		if(recebimentosLista[cliente->codigoCliente+i]->flag == 1) pos++;
	}
	return(pos);
}

int gerarNumDoc(Cliente cliente)
{
	int pos = proximoRecebimento(cliente);
	if(pos == 3) return -1;
	return(cliente->codigoCliente+pos);
}
Recebimento carregarRecebimento(unsigned int NumDoc)
{
	return(recebimentosLista[NumDoc]);
}

