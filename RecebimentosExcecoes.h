#ifndef RECEBIMENTOSEXCECOES_H
#define RECEBIMENTOSEXCECOES_H
#include "Cliente.h"
#include "Recebimentos.h"
#include "dependencias/stringHandling.h"
int registroDisponivel(Cliente cliente);
//Checa se e possivel salvar um novo recebimento.

int numeroDocumentoValido(unsigned int numDoc);
//Checar se numDoc esta dentro da lista de recebimentos.

#endif
