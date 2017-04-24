#ifndef RECEBIMENTOS_H
#define RECEBIMENTOS_H

#include "Recebimento.h"
#include "Cliente.h"
#include "RecebimentosExcecoes.h"

struct node {
	Cliente cliente;
	Recebimento rec[3];
	int recebimentosFeitos; 
};

typedef struct node* Node;
typedef struct node NODE_TAMANHO;

//ESSE OBJETO GUARDA um vetor de recebimentos
struct recebimentos {
	Node* nodes;
	int tamanho;
	int index;
};

typedef struct recebimentos Recebimentos;
typedef struct recebimentos REC_TAMANHO;

//devolve um array desse tipo com tamanho 50
Recebimentos novaListarecebimentos();

int tamanhoListaRecebimentos(Recebimentos* lista);

void destroirRecebimentos(Recebimentos* recebimentos);

void adicionarCliente(Recebimentos* lista, String nome, String endereco, String telefone);

void adicionarRecebimento(Recebimentos* lista, int codigoCliente, float valor, Data v);

void imprimirListaRecebimentos(Recebimentos* lista);	

int codigoClienteValido(Recebimentos* lista, int codigo);

void alterarDadosClientes(Recebimentos* lista, Cliente cliente);

Cliente pegarUmCliente(Recebimentos* lista, int codigo);

void imprimirDadosCliente(Recebimentos* lista, int codigo);

//retorna 1 se ainda pode, 0 senao
int recebimentosDisponiveis(Recebimentos* lista, int codigo);

Recebimentos novaListaRealocada();

#endif
