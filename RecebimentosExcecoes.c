#include "Recebimentosexcecoes.h"
#include "dependencias/stringHandling.h"
#include <stdio.h>
#include <stdlib.h>
#include "Cliente.h"
#include "Recebimentos.h"
#define DEBUG if(0)

int registroDisponivel(Cliente cliente)
{
	if(gerarNumDoc(cliente)==-1)
	{
		return -1;
	}
	else return gerarNumDoc(cliente);
}

//int numeroDocumentoValido(unsigned int numDoc);
//Desenvolver uma forma de encontrar o tamanho da lista de recebimentos e checar existencia de um dado numDoc nela.	
