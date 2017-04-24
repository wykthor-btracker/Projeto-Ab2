#include "TratamentoArquivos.c"
#include "Recebimentos.h"
#include "dependencias/stringHandling.h"
#include <stdio.h>
#include <stdlib.h>

const char CAMNHO[] = "recebimentos.dat"

/*
tamanho index
[info cliente 1,info rec 11, info rec 12, info rec 13]
[info cliente 2, info rec 21, info rec 22, info rec 23]
....

token separador $?

*/
void gravarRecebimentos(Recebimentos* lista) {
	int i;
	FILE* escritor = fopen(CAMNHO, "w");
	for(i = 0; i < lista->index; i++) {

	}
	fclose(escritor);
}

Recebimentos* bufferizarRecebimentos() {
	Recebimentos buffer;
	//.....
	return buffer;
}