#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model.h"


Pessoa pessoas[100];
int total = 0;

void adicionarPessoa(const char *nome, int idade){

    strcpy(pessoas[total].nome, nome);
    pessoas[total].idade = idade;
    total++;
}

void editarPessoa(int indice, const char *nome, int idade){
    if (indice < 0 || indice >= total) return;

    strcpy(pessoas[indice].nome, nome);
    pessoas[indice].idade = idade;
}

void removerPessoa(int indice){
    if (indice < 0 || indice >= total) return;
    
    for (int i = indice; i < total - 1; i++)
        pessoas[i] = pessoas[i + 1];

    total--;
}