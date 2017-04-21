#ifndef DATA_H
#define DATA_H

struct Data{
	int dia;
	int mes;
	int ano;
};

typedef struct Data Data;

int validaData(Data data);

void trocarDatas(Data *data1,Data *data2);

void ordenarDatas(Data *data1, Data *data2);

Data pegarDataAtual();

int calcDiferencaDatas(Data data);

#endif
