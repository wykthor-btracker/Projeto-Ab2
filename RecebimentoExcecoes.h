#ifndef RECEBIMENTOEXCECOES_H
#define RECEBIMENTOEXCECOES_H

#include "dependencias/stringHandling.h"
#include "dependencias/data.h"


// 1 -- dataVencimento maior que dataEmissao  0 -- dataVencimento menor que dataEmissao
int validarDataRecebimento(Data dataEmissao,Data dataVencimento);

#endif