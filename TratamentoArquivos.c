#include "TratamentoArquivos.h"
#include "Recebimentos.h"
#include "dependencias/stringHandling.h"
#include "Cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG if(1)

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
		fprintf(escritor, "%s$?%d$?%s$?%s", 
			cli->nome, cli->codigoCliente, cli->endereco, cli->telefone);
		//gravando dados dos recebimentos do cliente
		int recebFeitos = lista->nodes[i]->recebimentosFeitos;
		if(recebFeitos == 0)
			fprintf(escritor, "\n");
		else {
			for(j = 0; j < recebFeitos; j++) {
				Recebimento r = lista->nodes[i]->rec[j];
				fprintf(escritor, "#?%d$?%.2f$?%d$?%d$?%d$?%d$?%d$?%d$?%d$?%d",
					r->numeroDocumento, r->valorRecebimento,
					r->dataEmissao.dia, r->dataEmissao.mes,
					r->dataEmissao.ano, r->dataVencimento.dia, 
					r->dataVencimento.mes, r->dataVencimento.ano, 
					r->codigoCliente, r->flag);
			}
			printf("\n");
		}
	}
	fclose(escritor);
}

Recebimentos bufferizarRecebimentos() {
	Recebimentos buffer;
	int i, j;
	const char KEY[] = "$?";
	FILE* leitor = fopen(CAMNHO, "r");
	int tamanhoLista, indexLista;
	fscanf(leitor, "%d %d\n", &tamanhoLista, &indexLista);
	DEBUG printf("%d %d\n", tamanhoLista, indexLista);
	buffer.nodes = (Node*) malloc(sizeof(NODE_TAMANHO) * tamanhoLista);
	for(i = 0; i < tamanhoLista; i++)
		buffer.nodes[i] = novoNode();
	buffer.tamanho = tamanhoLista;
	buffer.index = indexLista;

	char linhaArquivo[10000];	

	for(i = 0; i < indexLista; i++) {
		Cliente c = buffer.nodes[i]->cliente;
		fgets(linhaArquivo, sizeof(linhaArquivo), leitor);
		DEBUG printf("==Linha pega %s\n", linhaArquivo);
		char* substring = strtok(linhaArquivo, KEY);
		copyString(c->nome, substring); 				  //get name
		DEBUG printf("==Nome: %s\n", substring);
		c->codigoCliente = stringToInt(strtok(NULL, KEY));//get codigo
		DEBUG printf("==Codigo cliente: %d\n", c->codigoCliente);
		copyString(c->endereco, strtok(NULL, KEY));//get endereco
		DEBUG printf("==endereco: %s\n", c->endereco);
		copyString(c->telefone, strtok(NULL, KEY));//get telefone 
		DEBUG printf("==endereco: %s\n", c->telefone);
		/*
		if(isEqual(strtok(NULL, KEY), "\n"))
			continue;
		else {
			int recFeitos = 0;
			for(j = 0; j < 3; j++) {
				recFeitos++;
				buffer.nodes[i]->rec[j] = (Recebimento) malloc(sizeof(receb));
				Recebimento r = buffer.nodes[i]->rec[j];
				r->numeroDocumento = stringToInt(strtok(NULL, KEY));
				r->valorRecebimento = atof(strtok(NULL, KEY));
				r->dataEmissao.dia = stringToInt(strtok(NULL, KEY));
				r->dataEmissao.mes = stringToInt(strtok(NULL, KEY));
				r->dataEmissao.ano = stringToInt(strtok(NULL, KEY));
				r->dataVencimento.dia = stringToInt(strtok(NULL, KEY));
				r->dataVencimento.mes = stringToInt(strtok(NULL, KEY));
				r->dataVencimento.ano = stringToInt(strtok(NULL, KEY));
				r->codigoCliente = stringToInt(strtok(NULL, KEY));
				r->flag = stringToInt(strtok(NULL, KEY));
				if(isEqual(strtok(NULL, KEY), "\n"))
					break;
			}
			buffer.nodes[i]->recebimentosFeitos = recFeitos;
		} */
	}	
	fclose(leitor);
	return buffer;
}
