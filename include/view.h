#ifndef VIEW_H
#define VIEW_H

#include "model.h"

void atualizarLista();

//Interface
void criarBotoes(GtkWidget *container);
void criarCampos(GtkWidget *container);
void criarLista(GtkWidget *container);

//Eventos
void onClickAdcionarPessoa(GtkWidget *widget, gpointer data);
void onClickEditarPessoa(GtkWidget *widget, gpointer data);
void onClickRemoverPessoa(GtkWidget *widget, gpointer data);
void ativar(GtkApplication *app, gpointer data);

#endif