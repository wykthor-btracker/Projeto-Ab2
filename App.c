#include "Cliente.h"
#include "ClienteExcecoes.h"
#include "Recebimento.h"
#include "RecebimentoExcecoes.h"
#include "Recebimentos.h"
#include "RecebimentosExcecoes.h"
#include "dependencias/stringHandling.h"
#include "dependencias/data.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>

#define DEBUG if(1)

Recebimento* recebimentosLista = NULL; //EH INICIADO NO MAIN
int recebTamaho, *pRecebeTamanho = &recebTamaho; //TAMANHO DESSA LISTA
//Cliente* clientes = NULL;

void cabecalho() {
	printf("|---------------------------------------------------------------------------------------------------|\n");
	printf("|                                         RECEBIMENTOS EMPRESA                                      |\n");
	printf("|                                           GNU-GLP license                                         |\n");
	printf("|                                         [version 1.0 - 2017]                                      |\n"); 
	printf("|---------------------------------------------------------------------------------------------------|\n");
}

void inserirNovoCliente() {
	int numeroClientes, i,val_indice,*indice = &val_indice,tamanhoBase,*pTamanho = &tamanhoBase;
	printf("Quantos clientes deseja adicionar? ");
	scanf("%d", &numeroClientes);
	getchar();
	Cliente* clientes = listaCliente(clientes,indice);
	DEBUG printf("Numero de entradas ja existentes:%d\n",*indice);
	atualizarClientes(numeroClientes,clientes,pTamanho);
	DEBUG printf("Indice novo:%d\n",*indice);
	int tamanho = *indice;
	for(i = tamanho; i < numeroClientes+tamanho; i++) {
		printf("Dados do cliente: \n");
		char nome[101];
		printf("Nome >>> ");
		scanf("%[^\n]", nome);
		getchar();
		char endereco[201];
		printf("Endereço >>> ");
		scanf("%[^\n]", endereco);
		getchar();
		char telefone[12];
		printf("Telefone >>> ");
		scanf("%[^\n]", telefone);
		getchar();
		unsigned int codigoCliente = *indice;		
		(*indice)++;
		clientes[i] = novoCliente(nome, endereco, telefone, codigoCliente);
		DEBUG {
			printf("Dados: \n");
			printf("nome: %s\n", nome);
			printf("endereco: %s\n", endereco);
			printf("telefone: %s\n", telefone);
			printf("codigoCliente: %u\n", codigoCliente);
		}
		DEBUG {
			printf("Estado cliente: \n");
			printf("nome: %s\n", pegarNome(clientes[i]));
			printf("endereco: %s\n", pegarEndereco(clientes[i]));
			printf("telefone: %s\n", pegarTelefone(clientes[i]));
			printf("codigoCliente: %u\n", pegarCodigoCliente(clientes[i]));
		}
	}
	DEBUG printf("Numero de entradas a serem salvas:%d\n",*indice);
	//GRAVANDO O OBJET
	int gravacaoOk = salvarClientes(clientes, (*indice));
	if(!gravacaoOk) DEBUG printf("Gravacao funcionou.\n");

}

void inserirNovoRecebimento() {
	printf("Já possui cadastro? (S/N) ");
	char resposta;
	scanf("%c", &resposta);
	getchar();
	resposta = toupper(resposta);
	if(resposta == 'S') {
		Cliente cliente = NULL;
		printf("Informe o código do cliente: ");
		int codigo;
		scanf("%d", &codigo);
		getchar();
		int tamanhoLista, *tamanhoPointer = &tamanhoLista, i;
		Cliente* clientes = listaCliente(clientes, tamanhoPointer);
		for(i = 0; i < tamanhoLista; i++) {
			if(clientes[i]->codigoCliente == codigo) {
				cliente = clientes[i];
			}
		}
		//mas pode ocorrer dele se esquecer na hora ou digitar um numero errado ou ate msm um numero q n existe
		if(cliente == NULL) inserirNovoRecebimento();
		DEBUG {
			printf("Dados cliente encontrado:\n");
			printf("Name: %s\n", pegarNome(cliente));
			printf("Telefone: %s\n", pegarTelefone(cliente));
			printf("Endereco: %s\n", pegarEndereco(cliente));
			printf("Codigo cliente: %d\n", pegarCodigoCliente(cliente));
		}
		int numeroDocumento = gerarNumDoc(cliente, recebimentosLista);
		if(numeroDocumento == -1)
			printf("Cliente já possui três recebimentos e não é possível inserir mais.\n");
		else {
			//fazer recebimento
		}
	} else {
		//cadastra cliente e faz o recebimento
		inserirNovoCliente();
		inserirNovoRecebimento();
	}
}

void alterarCadastroDeCliente() {
	printf("Insira o código do cliente: ");
	int codigo, tamanho, *tamanhoPointer = &tamanho, i, posicaoDoCliente = 0;
	scanf("%d", &codigo);
	getchar();
	Cliente cliente = NULL;
	Cliente* clientes = listaCliente(clientes, tamanhoPointer);
	for(i = 0; i < tamanho; i++) {
		if(clientes[i]->codigoCliente == codigo) {
			cliente = clientes[i];
			break;
		}
		posicaoDoCliente++;
	}
	DEBUG printf("Posicao do cliente: %d\n", posicaoDoCliente);
	//caso nao achou
	if(cliente == NULL) alterarCadastroDeCliente();
	printf("Escolha o que deseja alterar:\n");
	printf("	(1) Nome.\n");
	printf("	(2) Endereço.\n");
	printf("	(3) Telefone.\n");
	printf(">>> ");
	char opcao;
	scanf("%c", &opcao);
	getchar();
	char nome[101];
	char endereco[201];
	char telefone[12];
	switch(opcao) {
		case '1' :
			printf("Digite o nome do cliente: ");
			scanf("%[^\n]", nome);
			getchar();
			mudarNome(cliente, nome);
			break;
		case '2' :
			printf("Digite o Endereço: ");
			scanf("%[^\n]", endereco);
			getchar();
			mudarEndereco(cliente, endereco);
			break;
		case '3' :
			printf("Digite o telefone: ");
			scanf("%[^\n]", telefone);
			getchar();
			mudarTelefone(cliente, telefone);
			break;
		default :
			printf("Opção inválida.\n");
			alterarCadastroDeCliente();
			break;
	}
	//salve a alteracao
	int atualizacaoOk = atualizarCliente(clientes, tamanho, cliente);
	if(!atualizacaoOk) DEBUG printf("Gravacao funcionou.\n");
	else DEBUG printf("Gravacao falhou.\n");
}

void buscarRecebimentoPorData() {
	printf("4\n");
}

void menuPrincipal() {
	printf("Digite uma das opções: \n");
	printf("	(1) Inserir novo cliente.\n"); //ok
	printf("	(2) Inserir novo recebimento.\n");
	printf("	(3) Alterar cadastro do cliente.\n"); //ok
	printf("	(4) Buscar recebimentos por data.\n");
	printf("	(5) Encerrar programa.\n");
}

int main() {
	recebimentosLista = listarRecebimentos(recebimentosLista, pRecebeTamanho);
	system("clear");
	setlocale(LC_ALL, "Portuguese");
	char desligar = 'n';
	char opcao;
	while(desligar == 'n' || desligar == 'N') {
		cabecalho();
		menuPrincipal();
		printf(">>> ");
		scanf("%c", &opcao);
		DEBUG printf("***Opcao dada: %c\n", opcao);
		getchar();
		switch(opcao) {
			case '1' :
				inserirNovoCliente();
				break;
			case '2' :
				inserirNovoRecebimento();
				break;
			case '3' :
				alterarCadastroDeCliente();
				break;
			case '4' :
				buscarRecebimentoPorData();
				break;
			case '5' :
				exit(1);
				break;
			default :
				printf("Opção inválida.\n");
				break;
		}
		printf("Deseja fechar o programa (S/N)? ");
		scanf("%c", &desligar);
		getchar();
		DEBUG printf("***desligar? %c\n", desligar);
		system("clear");
	}
	return 0;
}
