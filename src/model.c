#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model.h"

sqlite3 *db;

void inicializarBanco(){
    int rc = sqlite3_open("pessoas.db", &db);

    if(rc){
        fprintf(stderr, "Erro ao abrir banco: %s\n", sqlite3_errmsg(db));
        return;
    }

    const char *sql =
        "CREATE TABLE IF NOT EXISTS pessoas ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "nome TEXT NOT NULL,"
        "idade INTEGER NOT NULL);";
    
    char *errMsg = 0;

    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);

    if(rc != SQLITE_OK){
        fprintf(stderr, "Erro SQL: %s\n", errMsg);
        sqlite3_free(errMsg);
    }
}

void adicionarPessoa(const char *nome, int idade){

    char sql[256];

    snprintf(sql, sizeof(sql), "INSERT INTO pessoas (nome, idade) VALUES ('%s', %d);", nome, idade);

    char *errMsg = 0;

    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);

    if(rc != SQLITE_OK){
        fprintf(stderr, "Erro ao inserir: %s\n", errMsg);
        sqlite3_free(errMsg);
    }
}

void editarPessoa(int id, const char *nome, int idade){
    char sql[256];

    snprintf(sql, sizeof(sql), "UPDATE pessoas SET nome='%s', idade=%d WHERE id=%d;",nome, idade, id);

    char *errMsg = 0;

    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);

    if(rc != SQLITE_OK){
        fprintf(stderr, "Erro ao editar: %s\n", errMsg);
        sqlite3_free(errMsg);
    }
}

void removerPessoa(int id){
    
    char sql[256];

    snprintf(sql, sizeof(sql), "DELETE FROM pessoas WHERE id = %d;", id);

    char *errMsg = 0;

    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);

    if(rc != SQLITE_OK){
        fprintf(stderr, "Erro ao remover: %s\n", errMsg);
        sqlite3_free(errMsg);
    }
}