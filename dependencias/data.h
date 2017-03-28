#ifndef DATA_H
#define DATA_H

struct Data{
	int dia;
	int mes;
	int ano;
};

typedef struct Data Data;

int validaData(Data data);


#endif