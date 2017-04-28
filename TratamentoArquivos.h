#ifndef TRATAMENTOARQUIVOS_H
#define TRATAMENTOARQUIVOS_H

#include "Recebimentos.h"

//se tiver vazio retorna 1, senao 0
int arquivoVazio(void);

void gravarRecebimentos(Recebimentos* lista);

Recebimentos* bufferizarRecebimentos(void);

#endif
