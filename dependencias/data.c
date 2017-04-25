#include "data.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG if(1)

// 1 -- TRUE 0 -- FALSE
int validaData(Data data){
	if(data.dia <= 31 && data.mes <= 12){
		if(data.ano >= 1000 && data.ano <= 9999){
			if((data.dia < 29 && data.mes == 2) || (data.mes == 2 && data.dia < 30 && (data.ano % 4 == 0 && (data.ano % 400 == 0 || data.ano % 100 != 0))))
				return 1;
			else if(data.dia <= 30 && (data.mes == 4 || data.mes == 6 || data.mes == 9 || data.mes == 11))
				return 1;
			else if(data.dia <= 31 && (data.mes == 1 || data.mes == 3 || data.mes == 5 || data.mes == 7 || data.mes == 8 || data.mes == 10 || data.mes == 12))
				return 1;
		}
	}

	return 0;
}

void trocarDatas(Data *data1, Data *data2){
	Data aux;

	aux.dia = data1->dia;
	aux.mes = data1->mes;
	aux.ano = data1->ano;

	data1->dia = data2->dia;
	data1->mes = data2->mes;
	data1->ano = data2->ano;

	data2->dia = aux.dia;
	data2->mes = aux.mes;
	data2->ano = aux.ano;
}

void ordenarDatas(Data *data1, Data *data2){
	Data aux;

	if(data1->ano > data2->ano){
		trocarDatas(data1,data2);
	}else if(data1->ano == data2->ano){
		if(data1->mes > data2->mes){
			trocarDatas(data1,data2);
		}else if(data1->mes == data2->mes){
			if(data1->dia > data2->dia){
				trocarDatas(data1,data2);
			}
		}
	}
}

Data pegarDataAtual(){
	time_t t = time(NULL);
  	struct tm* pointer = localtime(&t);
  	Data data;

  	data.dia = pointer->tm_mday;
  	data.mes = pointer->tm_mon+1;
  	data.ano = pointer->tm_year+1900;

  	return data;
}

int verificarDataVencimento(Data dataVencimento){
	Data dataEmissao = pegarDataAtual();

	DEBUG printf("****Data vencimento dada: %d/%d/%d\n", 
			dataVencimento.dia, dataVencimento.mes, dataVencimento.ano);

	if(dataVencimento.ano < dataEmissao.ano){
		return 0;
	}else if(dataVencimento.ano == dataEmissao.ano){
		if(dataVencimento.mes < dataEmissao.mes){
			return 0;
		}else if(dataVencimento.mes == dataEmissao.mes){
			if(dataVencimento.dia < dataEmissao.dia){
				return 0;
			}
		}
	}

	return 1;
}

int calcDiferencaDatas(Data data){
	time_t diaAtual;
	struct tm dataDesejada;
	double segundos;

	time(&diaAtual);
	
	dataDesejada = *localtime(&diaAtual);

	dataDesejada.tm_mday = data.dia;
	dataDesejada.tm_mon = data.mes-1;
	dataDesejada.tm_year = data.ano-1900;

	int dias = difftime(diaAtual,mktime(&dataDesejada)) / 86400;

	if(dias > 0)
		return abs(dias);

	return 0;
}