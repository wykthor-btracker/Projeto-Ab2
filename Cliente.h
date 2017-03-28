#ifndef CLIENTE_H
#define CLIENTE_H

#include "dependencias/stringHandling.h"

struct cliente {
	char nome[101];
	char endereco[201];
	char telefone[12];
	unsigned int codigoCliente;
	int contador;
};

/*
 * Remove a necessidade de digitar struct cliente
 * e trabalha diretamente com ponteiros para cada
 * objeto cliente.
 */
typedef struct cliente* Cliente;

/*
 * Sera utilizado na criacao dinamica dos objetos
 * clientes.
 */
typedef struct cliente tamanhoCliente;

/*
 * Essa funcao funciona como construtor
 * do objeto cliente.
 *
 * @param nome
 * @param endereco
 * @param telefone
 * @param codigo do cliente
 * @return um objeto cliente
 */
Cliente novoCliente(String nome, String endereco, 
	String telefone, unsigned int codigoCliente);

/*
 * Esse funcao retorna o nome do cliente.
 *
 * @param objeto cliente
 * @return o nome do cliente
 */
String pegarNome(Cliente cliente);

/*
 * Esse funcao retorna o endereco do cliente.
 *
 * @param objeto cliente
 * @return o endereco
 */
String pegarEndereco(Cliente cliente);

/*
 * Esse funcao retorna o telefone do cliente.
 *
 * @param objeto cliente
 * @return o telefone do cliente
 */
String pegarTelefone(Cliente cliente);

/*
 * Esse funcao retorna o codigo do cliente.
 *
 * @param objeto cliente
 * @return o codigo do cliente
 */
int pegarCodigoCliente(Cliente telefone);

/*
 * Essa funcao altera o nome do cliente.
 *
 * @param cliente que ira ser modificado.
 * @param o novo nome
 */
void mudarNome(Cliente cliente, String novoNome);

/*
 * Essa funcao altera o endereco do cliente.
 *
 * @param cliente que ira ser modificado.
 * @param o novo endereco
 */
void mudarEndereco(Cliente cliente, String novoEndereco);

/*
 * Essa funcao altera o telefone do cliente.
 *
 * @param cliente que ira ser modificado.
 * @param o novo telefone
 */
void mudarTelefone(Cliente cliente, String novoTelefone);

/*
 * Essa funcao altera o codigo do cliente.
 *
 * @param cliente que ira ser modificado.
 * @param o novo codigo
 */
void mudarCodigoCliente(Cliente cliente, unsigned int novoCodigo);

/*
 * Essa funcao retorna o contador do cliente
 *
 * @param cliente 
 * @param o contador
 */
int pegarContador(Cliente cliente);

/*
 * Essa funcao altera o contador do cliente.
 *
 * @param cliente que ira ser modificado.
 * @param o novo contador
 */
void mudarContador(Cliente cliente, int novoContador);

/*
 * Essa funcao funciona como um destrutor
 * que ira destruir as referencias dos objetos 
 * clientes criados.
 *
 * @param cliente que sera destruido.
 */
void destruirCliente(Cliente cliente);

#endif
