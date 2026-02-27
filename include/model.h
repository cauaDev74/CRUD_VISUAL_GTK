#ifndef MODEL_H
#define MODEL_H

typedef struct {
    char nome[50];
    int idade;
} Pessoa;

extern Pessoa pessoas[100];
extern int total;

void adicionarPessoa(const char *nome, int idade);
void editarPessoa(int indice, const char *nome, int idade);
void removerPessoa(int indice);

#endif
