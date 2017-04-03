#ifndef RECEBIMENTOS_H
#define RECEBIMENTOS_H

#include "Recebimento.h"
#include "Cliente.h"
#include "RecebimentosExcecoes.h"
//TODO
Recebimento *listarRecebimentos(int size, Recebimento *lista);
//Carregar a lista completa de recebimentos.
int salvarRecebimento(Recebimento recebimento,Cliente cliente,Recebimento *recebimentosLista);
//Ler arquivo, checar se o limite de recebimentos foi alcancado, caso nao,
//Encontrar lugar na lista em que o recebimento deve ser adicionado,
//Respeitando a associacao cod_cli+posReceb para indice. Retornar zero se for bem sucedido.

int proximoRecebimento(Cliente cliente,Recebimento *recebimentosLista);
//Retornar posicao do proximo recebimento.

void substituirRecebimento(Recebimento recebimento,unsigned int NumDoc);
//Substituir o documento novo pelo documento com o NumDoc atual.

Recebimento carregarRecebimento(unsigned int NumDoc,Recebimento *recebimentosLista);
//Devolver o recebimento correspondente.

Recebimento *carregarRecebimentosPorData(Data inicio,Data fim,Recebimento *recebimentosLista);
//Carregar recebimentos por data.

Recebimento copiarRecebimento(Recebimento novoRecebimento,Recebimento antigoRecebimento);
//Copiar um recebimento em outro.

int gerarNumDoc(Cliente cliente,Recebimento *recebimentosLista);
//Descobrir qual a posicao do proximo recebimento, somar isso a id do cliente.
//Resulta em indice na lista Recebimentos.
Recebimento *carregarRecebimentoPorCliente(Cliente cliente,Recebimento *recebimentos,Recebimento *recebimentosLista);
#endif
