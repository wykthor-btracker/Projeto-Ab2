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

char programaLidado = 's';

void cabecalho() {
	printf("|---------------------------------------------------------------------------------------|\n");
	printf("|                                   RECEBIMENTOS EMPRESA                                |\n");
	printf("|                                     GNU-GLP license                                   |\n");
	printf("|                                   [version 1.0 - 2017]                                |\n"); 
	printf("|---------------------------------------------------------------------------------------|\n");
	/*const int SCREN_SIZE = 100;
	int i;
	printf("|");
	for(i = 0; i < SCREN_SIZE; i++)
		printf("-");
	printf("|\n");
	printf("|"); */
}

void inserirNovoCliente() {
	printf("1\n");
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

void checkOpcao(const int* opcao) {
	switch(*opcao) {
		case 1 :
			inserirNovoCliente();
			break;
		case 2 :
			inserirNovoRecebimento();
			break;
		case 3 :
			alterarCadastroDeCliente();
			break;
		case 4 :
			buscarRecebimentoPorData();
			break;
		case 5 :
			exit(1);
			break;
		default :
			printf("Viado\n");
			break;
	}
}

void menuPrincipal() {
	int opcao;
	printf("Digite uma das opções: \n");
	printf("	(1) Inserir novo cliente.\n");
	printf("	(2) Inserir novo recebimento.\n");
	printf("	(3) Alterar cadastro do cliente.\n");
	printf("	(4) Buscar recebimentos por data.\n");
	printf("	(5) Encerrar programa.\n");
	scanf("%d", &opcao);
	checkOpcao(&opcao);
}

int main() {
	setlocale(LC_ALL, "Portuguese");
	menuPrincipal();

	return 0;
}
