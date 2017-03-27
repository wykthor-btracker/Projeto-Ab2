#ifndef CLIENTEEXCECOES_H
#define CLIENTEEXCECOES_H

#include "dependencias/stringHandling.h"

/*
 * Verifica se o nome dado e valido, se for 
 * retorna 1, senao 0;
 *
 * @param nome
 * @return 1 para valido, 0 para invalido
 */
int nomeValido(String nome);

/*
 * Verifica se o telefone dado e valido, se for 
 * retorna 1, senao 0;
 *
 * @param telefone
 * @return 1 para valido, 0 para invalido
 */
int telefoneValido(String telefone);

#endif

