#include "Recebimentos.h"
#include "Recebimento.h"
#include "RecebimentoExcecoes.h"
#include "Cliente.h"
#include "dependencias/data.h"
#include <stdio.h>
#include <stdlib.h>

#define DEBUG if(1)

Node novoNode() {
	Node node = (Node) malloc(sizeof(NODE_TAMANHO));
	node->cliente = (Cliente) malloc(sizeof(tamanhoCliente));
	int i;
	for(i = 0; i < 3; i++) {
		node->rec[i] = (Recebimento) malloc(sizeof(receb));
		node->recebimentosFeitos = 0;
	}
	return node;
}

Recebimentos novaListarecebimentos() {
	Recebimentos lista;
	lista.nodes = (Node*) malloc(sizeof(NODE_TAMANHO) * 50);
	int i;
	for(i = 0; i < 50; i++)
		lista.nodes[i] = novoNode();
	lista.tamanho = 50;
	lista.index = 0;
	return lista;
}
 
void adicionarCliente(Recebimentos* lista, String nome,
							 String endereco, String telefone) {
	lista->nodes[lista->index]->cliente = 
				novoCliente(nome, endereco, telefone, lista->index);
	printf("Código do novo cliente: %d\n", lista->index);
	lista->index++;
}

void adicionarRecebimento(Recebimentos* lista, 
					int codigoCliente, float valor) {
	int i, j;
	for(i = 0; i < lista->index; i++) {
		if(lista->nodes[i]->cliente->codigoCliente == codigoCliente) {
			for(j = 0; j < 3; j++) {
				DEBUG printf("Recebimentos feitos: %d\n", lista->nodes[i]->recebimentosFeitos);
				if(lista->nodes[i]->recebimentosFeitos == 3)
					printf("Cliente já atingiu número máximo de recebimentos.\n");
				else {
					Data hoje = pegarDataAtual();
					//data de vencimento -> 2 dias apos emissao
					Data vecimento = hoje;
					vecimento.dia += 2;
					lista->nodes[i]->rec[j] = novoRecebimento(codigoCliente + j,
															  valor,
															  hoje,
															  vecimento, 
															  codigoCliente);
					lista->nodes[i]->rec[j]->flag = 1; // o j esta em uso
					lista->nodes[i]->recebimentosFeitos++;
					DEBUG printf("Recebimento adicionado.\n");
					break;
				}
			}
		}
	}
}

int tamanhoListaRecebimentos(Recebimentos* lista) {
	return lista->index;
}

void destroirRecebimentos(Recebimentos* recebimentos) {

}

void imprimirListaRecebimentos(Recebimentos* lista) {
	int i;
	for(i = 0; i < lista->index; i++) {
		printf("Nome cliente: %s\n", lista->nodes[i]->cliente->nome);
		printf("Endereco cliente: %s\n", lista->nodes[i]->cliente->endereco);
		printf("Telefone cliente: %s\n", lista->nodes[i]->cliente->telefone);
		printf("codigo Cliente: %d\n", lista->nodes[i]->cliente->codigoCliente);
		int recebimentosDesseCliente = lista->nodes[i]->recebimentosFeitos, j;
		DEBUG printf("Recebimentos : %d\n", recebimentosDesseCliente);
		for(j = 0; j < recebimentosDesseCliente; j++) {
			Recebimento handle = lista->nodes[i]->rec[j];
			//printf("	Recebimento numero %d\n", j);
			printf("	Numero do documento: %d\n",  handle->numeroDocumento);
			printf("	Valor do documento : %.2f\n", handle->valorRecebimento);
			printf("	Data emissao: %d/%d/%d\n", handle->dataEmissao.dia, handle->dataEmissao.mes, handle->dataEmissao.ano);
			printf("	Data emissao: %d/%d/%d\n", handle->dataVencimento.dia, handle->dataVencimento.mes, handle->dataVencimento.ano);
		}
	}
} 
