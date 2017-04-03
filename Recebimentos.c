#include "Recebimentos.h"
#include "Recebimento.h"
#include "RecebimentoExcecoes.h"
#include "Cliente.h"
#include <stdio.h>
#include <stdlib.h>
//TODO
Recebimento *listarRecebimentos(int size, Recebimento *recebimentos)
{
	FILE *fw;
	int i;
	recebimentos = malloc(sizeof(receb)*size);
	for(i=0;i<size;i++) recebimentos[i] = malloc(sizeof(receb));
	if((fw = fopen("recebimentos.dat","r+"))==NULL) printf("SHIT\n");
	i = 0;
	while(fscanf(fw,"%u %f %d/%d/%d %d/%d/%d %u %d",
		&recebimentos[i]->numeroDocumento,
		&recebimentos[i]->valorRecebimento,
		&recebimentos[i]->dataEmissao.dia,
		&recebimentos[i]->dataEmissao.mes,
		&recebimentos[i]->dataEmissao.ano,
		&recebimentos[i]->dataVencimento.dia,
		&recebimentos[i]->dataVencimento.mes,
		&recebimentos[i]->dataVencimento.ano,
		&recebimentos[i]->codigoCliente,
		&recebimentos[i]->flag)!=EOF) i++;
	fclose(fw);
	return(recebimentos);
}	
Recebimento recebimentosLista[30];//Solucao temporaria pra falta de uma lista global de structs

Recebimento *carregarRecebimentoPorCliente(Cliente cliente,Recebimento *recebimentos,Recebimento *recebimentosLista)
{
	int i,size = 3;
	recebimentos = malloc(sizeof(receb)*size);
	for(i=0;i<size;i++) recebimentos[i] = malloc(sizeof(receb));	
	for(i=0;i<size;i++)
	{
		copiarRecebimento(carregarRecebimento((cliente->codigoCliente) + i,recebimentosLista),recebimentos[i]);
	}
	return(recebimentos);
}	

Recebimento *carregarRecebimentosPorData(Data inicio,Data fim,Recebimento *recebimentosLista)
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

int salvarRecebimento(Recebimento recebimento,Cliente cliente,Recebimento *recebimentosLista)
{
	 int id = registroDisponivel(cliente,recebimentosLista);
	 if(id == -1) return(0);
	 recebimentosLista[id] = copiarRecebimento(recebimentosLista[id],recebimento);
	 recebimentosLista[id]->flag = 1;
	 return 1;
}

int proximoRecebimento(Cliente cliente,Recebimento *recebimentosLista)
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

int gerarNumDoc(Cliente cliente,Recebimento *recebimentosLista)
{
	int pos = proximoRecebimento(cliente,recebimentosLista);
	if(pos == 3) return -1;
	return(cliente->codigoCliente+pos);
}
Recebimento carregarRecebimento(unsigned int NumDoc,Recebimento *recebimentosLista)
{
	return(recebimentosLista[NumDoc]);
}

