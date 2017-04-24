#include "RecebimentosExcecoes.h"
#include "dependencias/stringHandling.h"
#include <stdio.h>
#include <stdlib.h>
#include "Cliente.h"
#include "Recebimentos.h"
#ifndef	DEBUG
#define DEBUG if(0)
#endif

/*
int registroDisponivel(Cliente cliente,Recebimento *recebimentosLista)
{
	if(gerarNumDoc(cliente,recebimentosLista)==-1)
	{
		return -1;
	}
	else return gerarNumDoc(cliente,recebimentosLista);
}

int numeroDocumentoValido(unsigned int numDoc,int *tamanhoLista,Recebimento *lista)
{
	if(numDoc<=*tamanhoLista && lista[numDoc]->flag == 1) return 1;
	else return 0;
}
//Desenvolver uma forma de encontrar o tamanho da lista de recebimentos e checar existencia de um dado numDoc nela.	

*/