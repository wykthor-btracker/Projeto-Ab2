#ifndef RECEBIMENTOSEXCECOES_H
#define RECEBIMENTOSEXCECOES_H
#include "Cliente.h"
#include "Recebimentos.h"
#include "dependencias/stringHandling.h"

//1 se for invalido (negativo), 0 senao
int codigoClienteInvalido(const int codigoCliente);

//1 se for invalido (negativo), 0 senao
int codigoRecebimentoInvalido(const int codigoRecebimento);

#endif
