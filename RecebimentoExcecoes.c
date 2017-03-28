#include "RecebimentoExcecoes.h"
#include "dependencias/stringHandling.h"
#include "dependencias/data.h"
#include <stdio.h>
#include <stdlib.h>

int validarDataRecebimento(Data dataEmissao,Data dataVencimento){
	if(dataEmissao.ano < dataVencimento.ano){
		return 1;
	}else if(dataEmissao.ano == dataVencimento.ano){
		if(dataEmissao.mes <= dataVencimento.mes)
			if((dataEmissao.dia < dataVencimento.dia && dataEmissao.mes == dataVencimento.mes) || dataEmissao.mes < dataVencimento.mes)
				return 1;
	}
	
	return 0;
}