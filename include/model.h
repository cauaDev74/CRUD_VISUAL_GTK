#ifndef MODEL_H
#define MODEL_H

#include <sqlite3.h>

typedef struct {
    char nome[50];
    int idade;
} Pessoa;

extern sqlite3 *db;

void inicializarBanco();

void adicionarPessoa(const char *nome, int idade);
void editarPessoa(int indice, const char *nome, int idade);
void removerPessoa(int indice);

#endif
