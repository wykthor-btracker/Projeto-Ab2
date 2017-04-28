#include "TratamentoArquivos.h"
#include "Recebimentos.h"
#include "dependencias/stringHandling.h"
#include "Cliente.h"
#include <stdio.h>
#include <stdlib.h>

const char CAMNHO[] = "recebimentos.dat";

/*
tamanho index
[info cliente 1,info rec 11, info rec 12, info rec 13]
[info cliente 2, info rec 21, info rec 22, info rec 23]
....

token separador $?

*/

int arquivoVazio(void) {
	FILE* leitorDeTeste = fopen(CAMNHO, "r");
	int x, y;
	int estaVazio  = (fscanf(leitorDeTeste, "%d$?%d", &x, &y) == EOF);
	fclose(leitorDeTeste);
	return estaVazio;
}

void gravarRecebimentos(Recebimentos* lista) {
	int i, j;
	FILE* escritor = fopen(CAMNHO, "w");
	//gravando tamanho e posicao do index da lista
	fprintf(escritor, "%d %d\n", lista->tamanho, lista->index);
	for(i = 0; i < lista->index; i++) {
		Cliente cli = lista->nodes[i]->cliente;
		//gravando os dados do cliente
		fprintf(escritor, "%s$?%d$?%s$?%s$?", 
			cli->nome, cli->codigoCliente, cli->endereco, cli->telefone);
		//gravando dados dos recebimentos do cliente
		int recebFeitos = lista->nodes[i]->recebimentosFeitos;
		if(recebFeitos == 0)
			fprintf(escritor, "\n");
		else {
			for(j = 0; j < recebFeitos; j++) {
				Recebimento r = lista->nodes[i]->rec[j];
				fprintf(escritor, "%d$?%.2f$?%d$?%d$?%d$?%d$?%d$?%d$?%d$?%d\n",
					r->numeroDocumento, r->valorRecebimento,
					r->dataEmissao.dia, r->dataEmissao.mes,
					r->dataEmissao.ano, r->dataVencimento.dia, 
					r->dataVencimento.mes, r->dataVencimento.ano, 
					r->codigoCliente, r->flag);
			}
		}
	}
	fclose(escritor);
}

Recebimentos* bufferizarRecebimentos() {
	Recebimentos* buffer = NULL;
	const char KEY[] = "$?";
	FILE* leitor = fopen(CAMNHO, "r");
	int tamanhoLista, indexLista;
	fscanf(leitor, "%d %d", &tamanhoLista, &indexLista);
	//verifica se precisa getchar();
	fclose(leitor);
	return buffer;
}