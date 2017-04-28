#include "Cliente.h"
#include "ClienteExcecoes.h"
#include "Recebimento.h"
#include "RecebimentoExcecoes.h"
#include "Recebimentos.h"
#include "RecebimentosExcecoes.h"
#include "dependencias/stringHandling.h"
#include "dependencias/data.h"
#include "TratamentoArquivos.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>

#define DEBUG if(1)

//int clients = 0; //sempre q preciso atualize

Recebimentos gerenciadorLista; //lista global de recebimentos

void cabecalho() {
	printf("|---------------------------------------------------------------------------------------------------|\n");
	printf("|                                         RECEBIMENTOS EMPRESA                                      |\n");
	printf("|                                           GNU-GLP license                                         |\n");
	printf("|                                         [version 1.0 - 2017]                                      |\n"); 
	printf("|---------------------------------------------------------------------------------------------------|\n");
}

void inserirNovoCliente() {
	printf("Informe os dados do cliente: \n");
	printf("Nome: ");
	char nome[101];
	scanf("%[^\n]", nome);
	getchar();
	printf("Endereço: ");
	char endereco[201];
	scanf("%[^\n]", endereco);
	getchar();
	printf("Telefone: ");
	char telefone[12];
	scanf("%[^\n]", telefone);
	getchar();
	adicionarCliente(&gerenciadorLista, nome, endereco, telefone);
}

void inserirNovoRecebimento() {
	//um operador controla isso
	printf("Insira código do cliente: ");
	char entrada[20];
	scanf("%[^\n]", entrada);
	getchar();
	int codigo = stringToInt(entrada);
	if(codigo == -1) {
		inserirNovoCliente();
		inserirNovoRecebimento();
	} else {
		if(!codigoClienteValido(&gerenciadorLista, codigo)) {
			printf("Não encontramos o cliente pelo codigo fornecido.\n");
			//inserirNovoRecebimento();
		} else {
			int flag = recebimentosDisponiveis(&gerenciadorLista, codigo);
			DEBUG printf("==FLAG:%d\n", flag);
			if(!flag)
				printf("O cliente já atingiu o limite de recebimentos.\n");
			else {
				printf("Informe o valor da transação em Reais R$: ");
				float valor; 	
				scanf("%f", &valor);
				getchar();
				printf("Forneça a data de vencimento (dd/mm/ano) sem espaços: ");
				Data vencimento;
				scanf(" %d/%d/%d", &vencimento.dia, &vencimento.mes, &vencimento.ano);
				getchar();
				int dataOk = verificarDataVencimento(vencimento);
				if(!dataOk) {
					printf("Data fornecida e inválida.\n");
					inserirNovoRecebimento();
				} else {
					DEBUG printf("***dataOK : %d\n", dataOk);
					DEBUG printf("Codigo dado: %d\n", codigo);
					DEBUG printf("**Valor fornecido: %.2f\n", valor);
					DEBUG printf("**Data entrada: %d/%d/%d\n", vencimento.dia, vencimento.mes, vencimento.ano);
					adicionarRecebimento(&gerenciadorLista, codigo, valor, vencimento);
				}
			}
		}
	}
}

void alterarCadastroDeCliente() {
	printf("Insira o código do cliente: ");
	char entrada[20];
	scanf("%[^\n]", entrada);
	getchar();
	int codigo = stringToInt(entrada);
	if(!codigoClienteValido(&gerenciadorLista, codigo)) {
		printf("Não encontramos o cliente pelo código fornecido.\n");
		alterarCadastroDeCliente();
	} else {
		Cliente cliente = NULL;
		cliente = pegarUmCliente(&gerenciadorLista, codigo);
		DEBUG printf("Nome de cliente pego: %s\n", cliente->nome);
		DEBUG printf("ENdereco do cleinte pego: %s\n", cliente->endereco);
		DEBUG printf("Telefone do cliente pego: %s\n", cliente->telefone);
		DEBUG printf("Codigo cliente pego: %d\n", cliente->codigoCliente);
		printf("Escolha a opção do que deseja alterar: \n");
		char nome[101];
		char endereco[201];
		char telefone[12];
		printf("	(1) Nome.\n");
		printf("	(2) Endereço.\n");
		printf("	(3) Telefone.\n");
		printf(">>> ");
		char opcao;
		scanf("%c", &opcao);
		getchar();
		switch(opcao) {
			case '1' :
				printf("Informe o novo nome: ");
				scanf("%[^\n]", nome);
				getchar();
				copyString(cliente->nome, nome);
				break;
			case '2' :
				printf("Informe o novo endereço: ");
				scanf("%[^\n]", endereco);
				getchar();
				copyString(cliente->endereco, endereco);
				break;
			case '3' :
				printf("Informe o novo telefone: ");
				scanf("%[^\n]", telefone);
				getchar();
				copyString(cliente->telefone, telefone);
				break;
			default :
				printf("Opção inválida.\n");
				alterarCadastroDeCliente();
				break;
		}
		//isso garante o tratamento
		Cliente c = novoCliente(cliente->nome, cliente->endereco,
				 cliente->telefone, codigo);
		alterarDadosClientes(&gerenciadorLista, c);
	}
}

void buscarRecebimentoPorData() {
	//nao faz sentido cliente que nao tem cadastro ainda
	//vir solicitar recebimentos
	printf("Informe o código do cliente: ");
	char entrada[20];
	scanf("%[^\n]", entrada);
	getchar();
	int codigo = stringToInt(entrada);
	if(!codigoClienteValido(&gerenciadorLista, codigo)) {
		printf("Código fornecido não corresponde a nenhum cliente.\n");
	} else {
		int semRecebimentos = possuiRecebimentos(&gerenciadorLista, codigo);
		DEBUG printf("*******tem recebimento: %d\n", semRecebimentos);
		if(semRecebimentos) {
			printf("Esse cliente não possui recebimentos cadastrados.\n");
		} else {
			Data de, ate;
			printf("Informe o intervalo de datas que deseja buscar (dd/mm/ano):\n");
			printf("de: ");
			scanf("%d/%d/%d", &de.dia, &de.mes, &de.ano);
			getchar();
			printf("ate: "); 
			scanf("%d/%d/%d", &ate.dia, &ate.mes, &ate.ano);
			getchar();
			DEBUG printf("DE: %d/%d/%d\n", de.dia, de.mes, de.ano);
			DEBUG printf("Ate: %d/%d/%d\n", ate.dia, ate.mes, ate.ano);
			recebimentosPorData(&gerenciadorLista, codigo, de, ate);
		}
	}

}

void _imprimirListaRecebimentos() {
	imprimirListaRecebimentos(&gerenciadorLista);
}

void buscarDadosCliente() {
	printf("Informe o código do cliente: ");
	char entrada[20];
	scanf("%[^\n]", entrada);
	getchar();
	int codigo = stringToInt(entrada);
	if(!codigoClienteValido(&gerenciadorLista, codigo))
		printf("Cliente não encontrado.\n");
	else
		imprimirDadosCliente(&gerenciadorLista, codigo);
}

void menuPrincipal() {
	printf("Digite uma das opções: \n");
	printf("	(1) Inserir novo cliente.\n"); //ok
	printf("	(2) Inserir novo recebimento.\n");
	printf("	(3) Alterar cadastro do cliente.\n"); //ok
	printf("	(4) Buscar recebimentos por data.\n");
	printf("	(5) Buscar dados de um cliente.\n");
	printf("	(6) Imprimir todos os dados.\n"); //PARA TESTE
	printf("	(7) Encerrar programa.\n");
}

int main() {
	/*
	atualizar-->gravar por cima ("w")
	salvar -- >adicionar ao que ja tem ("a")

	int atualizar; //1 : atualizar, 0 salvar
	se arquivo tiver vazio
		geranciadorLista = novaListarecebimentos();
		salvar = 0
	else
		gerenciadorLista = bufferizarArquivo();
		salvar = 1
	*/
	/*
	system("clear");
	DEBUG printf("***Arquivo ta vazio? %d\n", arquivoVazio());
	gerenciadorLista = novaListarecebimentos();
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
				buscarDadosCliente();
				break;
			case '6':
				_imprimirListaRecebimentos();
				break;
			case '7' :
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
	} */
	/*
	se atualizar == 1
		gravarRecebimentos
	senao	

	
	*/

	int av = arquivoVazio();
	printf("Arquivo ta vazio? %d\n", av);
	gerenciadorLista = bufferizarRecebimentos();
	printf("Tamanho da lista: %d\n", gerenciadorLista.tamanho);
	printf("Index atual: %d\n", gerenciadorLista.index);

	//imprimirListaRecebimentos(&gerenciadorLista);

	////////gravarRecebimentos(&gerenciadorLista);
	//atualizaDadados(&gerenciadorLista);
	/////////destruirRecebimentos(&gerenciadorLista);

	/*
	Recebimentos gerenciadorLista = novaListarecebimentos();
	printf("tamanho %d\n", tamanhoListaRecebimentos(&gerenciadorLista));
	adicionarCliente(&gerenciadorLista, "Aurelio", "rua do aurelio", "88333");

	adicionarRecebimento(&gerenciadorLista, 0, 505);
	adicionarRecebimento(&gerenciadorLista, 0, 1);
	adicionarRecebimento(&gerenciadorLista, 0, 202);
	adicionarCliente(&gerenciadorLista, "Mario", "rua do mario", "284922222");
	imprimirListaRecebimentos(&gerenciadorLista);
	printf("tamanho %d\n", tamanhoListaRecebimentos(&gerenciadorLista));
	destroirRecebimentos(&gerenciadorLista); */
	return 0;
}
