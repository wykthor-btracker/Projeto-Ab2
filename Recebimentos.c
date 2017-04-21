#include "Recebimentos.h"
#include "Recebimento.h"
#include "RecebimentoExcecoes.h"
#include "Cliente.h"
#include "dependencias/data.h"
#include <stdio.h>
#include <stdlib.h>
//TODO
Recebimento *listarRecebimentos(Recebimento *recebimentos,int *tamanhoLista)
{
	FILE *leitorArquivo;
	int i = 0,tamanho = 1;
	recebimentos = malloc(sizeof(receb)*tamanho);
	recebimentos[i] = malloc(sizeof(receb));
	if((leitorArquivo = fopen("recebimentos.dat","r"))==NULL) printf("Fail to read recebimentos.dat .\n");
	while(fscanf(leitorArquivo,"%u %f %d/%d/%d %d/%d/%d %u %d",
		&recebimentos[i]->numeroDocumento,
		&recebimentos[i]->valorRecebimento,
		&recebimentos[i]->dataEmissao.dia,
		&recebimentos[i]->dataEmissao.mes,
		&recebimentos[i]->dataEmissao.ano,
		&recebimentos[i]->dataVencimento.dia,
		&recebimentos[i]->dataVencimento.mes,
		&recebimentos[i]->dataVencimento.ano,
		&recebimentos[i]->codigoCliente,
		&recebimentos[i]->flag)!=EOF)
		{ 
			i++;
			tamanho++;
			recebimentos = realloc(recebimentos,sizeof(receb)*tamanho);
			recebimentos[i] = malloc(sizeof(receb));
		}
	*tamanhoLista = i;
	fclose(leitorArquivo);
	return(recebimentos);
}
int salvarRecebimentosArquivo(Recebimento *recebimentos,int tamanho)
{
	FILE *escritorArquivo;
	int i;
	escritorArquivo = fopen("recebimentos.dat","w");
	for(i=0;i<tamanho;i++)
	{
		fprintf(escritorArquivo,"\n%u\n%f\n%d/%d/%d\n%d/%d/%d\n%u\n%d\n",
			recebimentos[i]->numeroDocumento,
			recebimentos[i]->valorRecebimento,
			recebimentos[i]->dataEmissao.dia,
			recebimentos[i]->dataEmissao.mes,
			recebimentos[i]->dataEmissao.ano,
			recebimentos[i]->dataVencimento.dia,
			recebimentos[i]->dataVencimento.mes,
			recebimentos[i]->dataVencimento.ano,
			recebimentos[i]->codigoCliente,
			recebimentos[i]->flag);
	}
	fclose(escritorArquivo);
	return 1;
}

Recebimento *atualizarRecebimentos(int extra,Recebimento *recebimentosLista,int *tamanhoLista)
{
	int i,tamanho = *tamanhoLista;
	recebimentosLista = realloc(recebimentosLista,(sizeof(receb))*(tamanho+extra));
	if(extra>0) for(i=tamanho;i<tamanho+extra;i++) recebimentosLista[i] = malloc(sizeof(receb));
	*tamanhoLista = tamanho+extra;
	return recebimentosLista;
}

Recebimento *carregarRecebimentoPorCliente(Cliente cliente,Recebimento *recebimentos,Recebimento *recebimentosLista)
{
	int i,tamanho = 3;
	recebimentos = malloc(sizeof(receb)*tamanho);
	for(i=0;i<tamanho;i++) recebimentos[i] = malloc(sizeof(receb));	
	for(i=0;i<tamanho;i++)
	{
		copiarRecebimento(carregarRecebimento((cliente->codigoCliente) + i,recebimentosLista),recebimentos[i]);
	}
	return(recebimentos);
}	

Recebimento *carregarRecebimentosPorData(Data inicio,Data fim,Recebimento *recebimentosLista)
{
		//Alocar espaco suficiente pra lista, comparar datas dadas como parametros
		//e retornar uma lista contendo todos os recebimentos requisitados.

	int i=0,aux=0,tamanho = 1,flag=0;
	Recebimento *listaRecebimento;
	listaRecebimento = malloc(sizeof(receb)*tamanho);

	ordenarDatas(&inicio,&fim);

	while(recebimentosLista[i] != NULL){
		if(recebimentosLista[i]->dataVencimento.ano > inicio.ano && recebimentosLista[i]->dataVencimento.ano < fim.ano){
			flag = 1;
		}else if(recebimentosLista[i]->dataVencimento.ano == inicio.ano || recebimentosLista[i]->dataVencimento.ano == fim.ano){
			if(inicio.ano == fim.ano){
				if(recebimentosLista[i]->dataVencimento.mes > inicio.mes && recebimentosLista[i]->dataVencimento.mes < fim.mes){
					flag = 1;
				}

				if(inicio.mes == fim.mes){
					if(recebimentosLista[i]->dataVencimento.dia >= inicio.dia && recebimentosLista[i]->dataVencimento.dia <= fim.dia){
						flag = 1;
					}
				}else{
					if(recebimentosLista[i]->dataVencimento.mes == inicio.mes){
						if(recebimentosLista[i]->dataVencimento.dia >= inicio.dia){
							flag = 1;
						}
					}
					if(recebimentosLista[i]->dataVencimento.mes == fim.mes){
						if(recebimentosLista[i]->dataVencimento.dia <= fim.dia){
							flag = 1;
						}
					}
				}
			}else{
				if(recebimentosLista[i]->dataVencimento.ano == inicio.ano){
					if(recebimentosLista[i]->dataVencimento.mes > inicio.mes)
						flag = 1;
					if(recebimentosLista[i]->dataVencimento.mes == inicio.mes && recebimentosLista[i]->dataVencimento.dia >= inicio.dia)
						flag = 1;
				}

				if(recebimentosLista[i]->dataVencimento.ano == fim.ano){
					if(recebimentosLista[i]->dataVencimento.mes < fim.mes)
						flag = 1;
					if(recebimentosLista[i]->dataVencimento.mes == fim.mes && recebimentosLista[i]->dataVencimento.dia <= fim.dia)
						flag = 1;
				}				

			}
		}
				
		if(flag){
			listaRecebimento[aux] = recebimentosLista[i];
			aux++;
			tamanho++;
			listaRecebimento = realloc(listaRecebimento,sizeof(receb)*tamanho);
			listaRecebimento[i] = malloc(sizeof(receb));
		}

		i++;
		flag=0;
	}

	return listaRecebimento;
}

Recebimento copiarRecebimento(Recebimento antigoRecebimento,Recebimento novoRecebimento)
{
	antigoRecebimento->numeroDocumento = novoRecebimento->numeroDocumento;
	antigoRecebimento->valorRecebimento = novoRecebimento->valorRecebimento;
	antigoRecebimento->dataEmissao = novoRecebimento->dataEmissao;
	antigoRecebimento->dataVencimento = novoRecebimento->dataVencimento;
	antigoRecebimento->codigoCliente = novoRecebimento->codigoCliente;
	antigoRecebimento->flag = novoRecebimento->flag;
	return(antigoRecebimento);
}

int salvarRecebimento(Recebimento recebimento,Cliente cliente,Recebimento *recebimentosLista)
{
	 int id = registroDisponivel(cliente,recebimentosLista);
	 if(id == -1) return(0);
	 recebimentosLista[id] = copiarRecebimento(recebimentosLista[id],recebimento);
	 recebimentosLista[id]->flag = 1;
	 return 1;
}

int proximoRecebimento(Cliente cliente,Recebimento *recebimentosLista)
{
	//Recebimentos eh uma lista global que contem em cada elemento uma struct do tipo Recebimento.
	//E o indice do recebimento corresponde a seu cliente e sua posicao na lista de recebimentos, ex:
	//cliente 2, recebimento 2, id = 2+2 = 4, esse recebimento estara na posicao 4 da lista Recebimentos.	
	int i,pos = 0;
	for(i=0;i<3;i++)
	{
		if(recebimentosLista[cliente->codigoCliente+i]->flag == 1) pos++;
	}
	return(pos);
}

int gerarNumDoc(Cliente cliente,Recebimento *recebimentosLista)
{
	int pos = proximoRecebimento(cliente,recebimentosLista);
	if(pos == 3) return -1;
	return(cliente->codigoCliente+pos);
}

Recebimento carregarRecebimento(unsigned int NumDoc,Recebimento *recebimentosLista)
{
	return(recebimentosLista[NumDoc]);
}

Cliente *listaCliente(Cliente *lista,int* tamanhoListaClientes)
{
	FILE *leitor;
	int i = 0,tamanho = 2;//Tamanho da lista deve ser maior que o numero de elementos por causa de um bug nao resolvido com fscanf.
	lista = malloc(sizeof(tamanhoCliente)*tamanho);
	lista[i] = malloc(sizeof(tamanhoCliente));
	if((leitor = fopen("cliente.dat","r"))==NULL)printf("Not able to open file");
	while((fscanf(leitor,"%s %s %s %d %d",
		lista[i]->nome,
		lista[i]->endereco,
		lista[i]->telefone,
		&lista[i]->codigoCliente,
		&lista[i]->contador))!=EOF)
		{
			i++;
			tamanho++;
			lista = realloc(lista,sizeof(tamanhoCliente)*tamanho);
			lista[i] = malloc(sizeof(tamanhoCliente));
		}
	fclose(leitor);
	*tamanhoListaClientes = i;
	return(lista);	
}

int salvarClientes(Cliente *clientes,int tamanho)
{
	FILE *escritor;
	int i;
	if((escritor = fopen("cliente.dat","w"))==NULL) printf("Fail to write on cliente.dat\n");
	for(i=0;i<tamanho;i++)
	{
		fprintf(escritor,"%s %s %s %d %d\n",
				clientes[i]->nome,
				clientes[i]->endereco,
				clientes[i]->telefone,
				clientes[i]->codigoCliente,
				clientes[i]->contador+1);
	}
	fclose(escritor);
	return 0;
}

Cliente *atualizarClientes(int extra,Cliente *clientesLista,int *tamanhoListaCliente)
{
	int i,tamanho = *tamanhoListaCliente;
	clientesLista = realloc(clientesLista,(sizeof(tamanhoCliente))*(tamanho+extra));
	if(extra>0) for(i=tamanho;i<(tamanho-1)+extra;i++) clientesLista[i] = malloc(sizeof(tamanhoCliente));
	*tamanhoListaCliente = (tamanho-1)+extra;
	return clientesLista;
}

