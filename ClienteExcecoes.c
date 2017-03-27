#include "ClienteExcecoes.h"
#include "dependencias/stringHandling.h"
#include <stdio.h>
#include <stdlib.h>

#define DEBUG if(0)

int nomeValido(String nome) {
	DEBUG printf("Inside nomeValido()\n");
	const int TAMANHO = stringSize(nome);
	DEBUG printf("TAMANHO: %d\n", TAMANHO);
	int i;
	for(i = 0; i < TAMANHO; i++) {
		DEBUG printf("character: %c\n", nome[i]);
		if(!(isChar(nome[i]) || isCapitalChar(nome[i]) || nome[i] == ' '))
			return 0;
	}
	return 1;
}

int telefoneValido(String telefone) {
	DEBUG printf("Inside telefoneValido()\n");
	const int TAMANHO = stringSize(telefone);
	DEBUG printf("TAMANHO: %d\n", TAMANHO);
	int i;
	for(i = 0; i < TAMANHO; i++) {
		DEBUG printf("character: %c\n", telefone[i]);
		if(isChar(telefone[i]) || isCapitalChar(telefone[i])) 
			return 0; 
	}
	return 1;
}
