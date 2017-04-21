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

#define DEBUG if(0)

void cabecalho() {
	printf("|---------------------------------------------------------------------------------------|\n");
	printf("|                                   RECEBIMENTOS EMPRESA                                |\n");
	printf("|                                     GNU-GLP license                                   |\n");
	printf("|                                   [version 1.0 - 2017]                                |\n"); 
	printf("|---------------------------------------------------------------------------------------|\n");
}

void inserirNovoCliente() {
	int numeroClientes, i;
	printf("Quantos clientes deseja adicionar? ");
	scanf("%d", &numeroClientes);
	getchar();
	Cliente* clientes = (Cliente*) 
			malloc(sizeof(Cliente) * numeroClientes); 
	//alocando o espaco de cada obj cliente para depois usar
	for(i = 0; i < numeroClientes; i++)
		clientes[i] = (Cliente) malloc(sizeof(tamanhoCliente));

	for(i = 0; i < numeroClientes; i++) {
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
		unsigned int codigoCliente;
		printf("Codigo >>> ");
		scanf("%u", &codigoCliente);
		getchar();
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
	//O PROBLEMA EH AQUI
	int gravacaoOk = salvarClientes(clientes, numeroClientes);
	if(!gravacaoOk) DEBUG printf("Gravacao funcionou.\n");
	for(i = 0; i < numeroClientes; i++)
		destruirCliente(clientes[i]);
}

void inserirNovoRecebimento() {
	printf("2\n");
}

void alterarCadastroDeCliente() {
	printf("3\n");
}

void buscarRecebimentoPorData() {
	printf("4\n");
}

void menuPrincipal() {
	printf("Digite uma das opções: \n");
	printf("	(1) Inserir novo cliente.\n");
	printf("	(2) Inserir novo recebimento.\n");
	printf("	(3) Alterar cadastro do cliente.\n");
	printf("	(4) Buscar recebimentos por data.\n");
	printf("	(5) Encerrar programa.\n");
}

int main() {
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
