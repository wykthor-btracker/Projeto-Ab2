#include "Recebimentos.h"
#include "Recebimento.h"
#include "Cliente.h"
#include <stdio.h>
//TODO
int RecebimentosRestantes(Cliente cliente)
{
	//Recebimentos eh uma lista global que contem em cada elemento uma struct do tipo Recebimento.
	int i,restantes = 3;
	for(i=0;i<2;i++)
	{
		if(Recebimentos[cliente->codigoCliente+i].flag == 1) restantes--;
	}
	return restantes;
}
void SubstituirRecebimento(Recebimento recebimento,unsigned int NumDoc)
{
	Recebimentos[NumDoc] = recebimento;
}
int main()
{
	return 0;
}
