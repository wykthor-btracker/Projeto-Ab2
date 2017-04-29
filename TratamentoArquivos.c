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
			fprintf(escritor, "$?#\n");
		else {
			for(j = 0; j < recebFeitos; j++) {
				Recebimento r = lista->nodes[i]->rec[j];
				fprintf(escritor, "$?%d$?%.2f$?%d$?%d$?%d$?%d$?%d$?%d$?%d$?%d",
					r->numeroDocumento, r->valorRecebimento,
					r->dataEmissao.dia, r->dataEmissao.mes,
					r->dataEmissao.ano, r->dataVencimento.dia, 
					r->dataVencimento.mes, r->dataVencimento.ano, 
					r->codigoCliente, r->flag);
			}
			fprintf(escritor, "$?#\n");
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
		substring = strtok(NULL, KEY);
		c->codigoCliente = stringToInt(substring);//get codigo
		DEBUG printf("==Codigo cliente: %d\n", c->codigoCliente);
		substring = strtok(NULL, KEY);
		copyString(c->endereco, substring);//get endereco
		DEBUG printf("==endereco: %s\n", c->endereco);
		substring = strtok(NULL, KEY);
		copyString(c->telefone, substring);//get telefone 
		DEBUG printf("==endereco: %s\n", c->telefone);
		
		substring = strtok(NULL, KEY);
		char tempNumDoc[10];
		copyString(tempNumDoc, substring);

		DEBUG printf("===depois de cliente:%s\n", tempNumDoc);
		if(isEqual(tempNumDoc, "#\n")) {
			DEBUG printf("===FIM===\n");
			continue;
		}
		
		else {
			int recFeitos = 0;
			for(j = 0; j < 3; j++) {
				recFeitos++;
				Recebimento r = buffer.nodes[i]->rec[j];
				if(j == 0)
					r->numeroDocumento = stringToInt(tempNumDoc);
				else {
					//substring = strtok(NULL, KEY);
					r->numeroDocumento = stringToInt(substring);
				}
				DEBUG printf("==numDoc: %d\n", r->numeroDocumento);
				substring = strtok(NULL, KEY);
				r->valorRecebimento = atof(substring);
				DEBUG printf("==Valor rec: %.2f\n", r->valorRecebimento);
				substring = strtok(NULL, KEY);
				r->dataEmissao.dia = stringToInt(substring);
				DEBUG printf("==DE dia: %d\n", r->dataEmissao.dia);
				substring = strtok(NULL, KEY);
				r->dataEmissao.mes = stringToInt(substring);
				DEBUG printf("==DE mes: %d\n", r->dataEmissao.mes);
				substring = strtok(NULL, KEY);
				r->dataEmissao.ano = stringToInt(substring);
				DEBUG printf("==DE ano: %d\n", r->dataEmissao.ano);
				substring = strtok(NULL, KEY);
				r->dataVencimento.dia = stringToInt(substring);
				DEBUG printf("==DV dia: %d\n", r->dataVencimento.dia);
				substring = strtok(NULL, KEY);
				r->dataVencimento.mes = stringToInt(substring);
				DEBUG printf("==DV mes: %d\n", r->dataVencimento.mes);
				substring = strtok(NULL, KEY);
				r->dataVencimento.ano = stringToInt(substring);
				DEBUG printf("==DV ano: %d\n", r->dataVencimento.ano);
				substring = strtok(NULL, KEY);
				r->codigoCliente = stringToInt(substring);
				DEBUG printf("==Codigo cliente: %d\n", r->codigoCliente);
				substring = strtok(NULL, KEY);
				r->flag = stringToInt(substring);
				DEBUG printf("==Flag: %d\n", r->flag);
				substring = strtok(NULL, KEY);
				DEBUG printf("%s\n", substring);
				if(isEqual(substring, "#\n")) {
					DEBUG printf("===FIM===\n");
					break;
				} 
			} 
			buffer.nodes[i]->recebimentosFeitos = recFeitos; 
		} 
	}	
	fclose(leitor);
	return buffer;
}
