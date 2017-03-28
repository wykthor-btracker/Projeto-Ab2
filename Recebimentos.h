#ifndef RECEBIMENTOS_H
#define RECEBIMENTOS_H

#include "Recebimento.h"
#include "Cliente.h"

//TODO
int SalvarRecebimento(Recebimento recebimento,Cliente cliente);
//Ler arquivo, checar se o limite de recebimentos foi alcancado, caso nao,
//Encontrar lugar na lista em que o recebimento deve ser adicionado,
//Respeitando a associacao cod_cli para indice. Retornar zero se for bem sucedido.

int RecebimentosRestantes(Cliente cliente);
//Retornar quantos recebimentos novos sao possiveis.

void SubstituirRecebimento(Recebimento recebimento,unsigned int NumDoc);
//Substituir o documento novo pelo documento com o NumDoc atual.

Recebimento CarregarRecebimento(unsigned int NumDoc);
//Devolver o recebimento correspondente.

char *GerarNumDoc(Recebimento recebimento,Cliente cliente);
//Descobrir quantos recebimentos restantes existem para o cliente.
//Concatenar esse numero com o id do cliente, devolver resultado.
int *IdDoDocumento(char *NumDoc);

#endif
