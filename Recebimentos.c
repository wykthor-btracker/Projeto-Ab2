#include "Recebimentos.h"
#include "Recebimento.h"
#include "RecebimentoExcecoes.h"
#include "Cliente.h"
#include "dependencias/data.h"
#include "dependencias/stringHandling.h"
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
	DEBUG printf("Cliente inserido\n");
}

void adicionarRecebimento(Recebimentos* lista, 
					int codigoCliente, float valor, Data v) {
	int i, j;
	DEBUG printf("**Inside add rece.\n");
	DEBUG printf("**essa lista vai ate: %d\n", lista->index);
	for(i = 0; i < lista->index; i++) {
		if(lista->nodes[i]->cliente->codigoCliente == codigoCliente) {
			DEBUG printf("**Achou o cliente pelo codigo.\n");
			DEBUG printf("**Recebimentos ja feitos por esse cliente: %d\n", lista->nodes[i]->recebimentosFeitos);
				if(lista->nodes[i]->recebimentosFeitos == 3)
					printf("Cliente já atingiu número máximo de recebimentos.\n");
				else {
					for(j = lista->nodes[i]->recebimentosFeitos; j < 3; j++) {
						Data hoje = pegarDataAtual();
						//data de vencimento -> 2 dias apos emissao
						//Data vecimento = hoje;
						//vecimento.dia += 2;
						DEBUG printf("**Numero do documento : %d\n", codigoCliente + j);
						DEBUG printf("**valor R$ %.f\n", valor);
						lista->nodes[i]->rec[j] = novoRecebimento(codigoCliente + j,
																  valor,
																  hoje,
																  v, 
																  codigoCliente);
						lista->nodes[i]->rec[j]->flag = 1; // o j esta em uso
						lista->nodes[i]->recebimentosFeitos++;
						DEBUG printf("Recebimento adicionado.\n");
						break;
					}
				}
		} else {
			DEBUG printf("nao achou cliente pelo codigo.\n");
		}
	}
	//printf("Não encontramos o cliente pelo codigo fornecido.\n");
}

int codigoClienteValido(Recebimentos* lista, int codigo) {
	int i;
	for(i = 0; i < lista->index; i++) 
		if(lista->nodes[i]->cliente->codigoCliente == codigo)
			return 1;
	return 0;
}

int tamanhoListaRecebimentos(Recebimentos* lista) {
	return lista->index;
}

void destruirRecebimentos(Recebimentos* recebimentos) {
	int i, j;
	for(i = 0; i < recebimentos->index; i++) {
		free(recebimentos->nodes[i]->cliente);
		for(j = 0; j < 3; j++)
			free(recebimentos->nodes[i]->rec[j]);
		free(recebimentos->nodes[i]);
	}
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
			printf("	Data de emissão: %d/%d/%d\n", handle->dataEmissao.dia, handle->dataEmissao.mes, handle->dataEmissao.ano);
			printf("	Data de vecimento: %d/%d/%d\n", handle->dataVencimento.dia, handle->dataVencimento.mes, handle->dataVencimento.ano);
		}
	}
} 

Cliente pegarUmCliente(Recebimentos* lista, int codigo) {
	int i;
	for(i = 0; i < lista->index; i++)
		if(lista->nodes[i]->cliente->codigoCliente == codigo)
			return lista->nodes[i]->cliente;
	return NULL;
}

void alterarDadosClientes(Recebimentos* lista, Cliente cliente) {
	int i;
	for(i = 0; i < lista->index; i++) 
		if(lista->nodes[i]->cliente->codigoCliente == cliente->codigoCliente)
			lista->nodes[i]->cliente = cliente;
	DEBUG printf("Dados alterados.\n");
}

void imprimirDadosCliente(Recebimentos* lista, int codigo) {
	int i, j;
	for(i = 0; i < lista->index; i++) {
		if(lista->nodes[i]->cliente->codigoCliente == codigo) {
			printf("-----------------------------------------------------\n");
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
				printf("	Data de emissão: %d/%d/%d\n", handle->dataEmissao.dia, handle->dataEmissao.mes, handle->dataEmissao.ano);
				printf("	Data de vecimento: %d/%d/%d\n", handle->dataVencimento.dia, handle->dataVencimento.mes, handle->dataVencimento.ano);
			}
			printf("-----------------------------------------------------\n");
		}
		break;
	}
}

int recebimentosDisponiveis(Recebimentos* lista, int codigo) {
	int i, toReturn;
	DEBUG printf("Dentro de recebimentosValidos.\n");
	for(i = 0; i < lista->index; i++) 
		if(lista->nodes[i]->cliente->codigoCliente == codigo) {
			toReturn = lista->nodes[i]->recebimentosFeitos < 3;
		}
	return toReturn;
}

int possuiRecebimentos(Recebimentos* lista, int codigo) { 
	int i;
	for(i = 0; i < lista->index; i++)
		return lista->nodes[i]->recebimentosFeitos == 0;
}

void recebimentosPorData(Recebimentos* lista,
			 int codigo, Data de, Data ate) {
	int i, j;
	for(i = 0; i < lista->index; i++) {
		if(lista->nodes[i]->cliente->codigoCliente == codigo) {
			printf("tem receb\n");
			Cliente cli = lista->nodes[i]->cliente;
			printf("Cliente: %s\n", pegarNome(cli));
			int recebimentosDesseCliente = lista->nodes[i]->recebimentosFeitos;
			for(j = 0; j < recebimentosDesseCliente; j++) {
				Recebimento r = lista->nodes[i]->rec[j];
				printf("Recebimento %d:\n", j);
				printf("	Valor: R$ %.2f\n", r->valorRecebimento);
				printf("	Vencimento: %d/%d/%d\n", r->valorRecebimento, r->dataVencimento.dia,
					 r->dataVencimento.mes, r->dataVencimento.ano);
				printf("	Dias de atraso: %d\n", calcDiferencaDatas(r->dataVencimento));
			}
		}
	}
}
