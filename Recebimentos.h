#ifndef RECEBIMENTOS_H
#define RECEBIMENTOS_H

#include "Recebimento.h"
#include "Cliente.h"
#include "RecebimentosExcecoes.h"
//TODO
Recebimento *listarRecebimentos(Recebimento *recebimentos,int *tamanhoLista);
//Carregar a lista completa de recebimentos.
//Atualizar o marcador que guarda o tamanho atual da lista.

int salvarRecebimento(Recebimento recebimento,Cliente cliente,Recebimento *recebimentosLista);
//Ler arquivo, checar se o limite de recebimentos foi alcancado, caso nao,
//Encontrar lugar na lista em que o recebimento deve ser adicionado,
//Respeitando a associacao cod_cli+posReceb para indice. Retornar zero se for bem sucedido.

Recebimento *atualizarRecebimentos(int extra,Recebimento *recebimentosLista,int *tamanhoLista);
//Realocar lista para adicionar ou removar posicoes, gerar os mallocs necessarios para as novas posicoes disponiveis.

int proximoRecebimento(Cliente cliente,Recebimento *recebimentosLista);
//Retornar posicao do proximo recebimento.

void substituirRecebimento(Recebimento recebimento,unsigned int NumDoc);
//Substituir o documento novo pelo documento com o NumDoc atual.

Recebimento carregarRecebimento(unsigned int NumDoc,Recebimento *recebimentosLista);
//Devolver o recebimento correspondente.

int salvarRecebimentosArquivo(Recebimento *lista,int tamanho);
//Salvar lista de recebimentos para o arquivo.
Recebimento *carregarRecebimentosPorData(Data inicio,Data fim,Recebimento *recebimentosLista);
//Carregar recebimentos por data.

Recebimento copiarRecebimento(Recebimento antigoRecebimento,Recebimento novoRecebimento);
//Copiar um recebimento em outro.

int gerarNumDoc(Cliente cliente,Recebimento *recebimentosLista);
//Descobrir qual a posicao do proximo recebimento, somar isso a id do cliente.
//Resulta em indice na lista Recebimentos.
Recebimento *carregarRecebimentoPorCliente(Cliente cliente,Recebimento *recebimentos,Recebimento *recebimentosLista);

Cliente *listaCliente(Cliente *lista,int* tamanhoListaClientes);
//Ler arquivo de clientes, gerar array de structs equivalente.

int salvarClientes(Cliente *clientes,int tamanho);
//Salva array de structs para o arquivo.

Cliente *atualizarClientes(int extra,Cliente *clientesLista,int *tamanhoListaCliente);
//Re-ajustar tamanho da lista de clientes.
#endif
