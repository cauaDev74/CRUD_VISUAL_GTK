#include <gtk/gtk.h>
#include <sqlite3.h>
#include "model.h"
#include "view.h"

#define RESOLUCTION_Y 600
#define RESOLUCTION_X 800

//Widgets Globais
GtkWidget *entryNome; //Campo Nome
GtkWidget *entryIdade; //Campo Idade
GtkWidget *listaPessoas; //Lista que será impressa
GtkWidget *botaoAdicionarPessoa; //Botão para adicionar pessoa
GtkWidget *botaoEditarPessoa; //Botão para editar pessoa
GtkWidget *botaoRemoverPessoa; //Botão para remover pessoa

void atualizarLista() {

    GList *children, *iter;

    children = gtk_container_get_children(GTK_CONTAINER(listaPessoas));

    for (iter = children; iter != NULL; iter = g_list_next(iter)) {
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    }

    g_list_free(children);

    const char *sql = "SELECT id, nome, idade FROM pessoas;";

    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro SELECT: %s\n", sqlite3_errmsg(db));
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {

        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *nome = sqlite3_column_text(stmt, 1);
        int idade = sqlite3_column_int(stmt, 2);

        char texto[100];

        snprintf(texto, sizeof(texto),
                 "%d - %s - %d anos",
                 id, nome, idade);

        GtkWidget *label = gtk_label_new(texto);

        gtk_list_box_insert(GTK_LIST_BOX(listaPessoas), label, -1);
    }

    sqlite3_finalize(stmt);

    gtk_widget_show_all(listaPessoas);
}

void criarBotoes(GtkWidget *container) {

    GtkWidget *botoesBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

    gtk_box_pack_start(GTK_BOX(container), botoesBox, FALSE, FALSE, 0);

    botaoAdicionarPessoa = gtk_button_new_with_label("Adicionar");

    botaoEditarPessoa = gtk_button_new_with_label("Editar");

    botaoRemoverPessoa = gtk_button_new_with_label("Remover");

    gtk_box_pack_start(GTK_BOX(botoesBox), botaoAdicionarPessoa, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(botoesBox), botaoEditarPessoa, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(botoesBox), botaoRemoverPessoa, TRUE, TRUE, 0);

    g_signal_connect(botaoAdicionarPessoa, "clicked", G_CALLBACK(onClickAdicionarPessoa), NULL);

    g_signal_connect(botaoEditarPessoa, "clicked", G_CALLBACK(onClickEditarPessoa), NULL);

    g_signal_connect(botaoRemoverPessoa, "clicked", G_CALLBACK(onClickRemoverPessoa), NULL);
}

void criarCampos(GtkWidget *container) {

    GtkWidget *frame =
        gtk_frame_new("Dados da Pessoa");

    gtk_box_pack_start(GTK_BOX(container), frame, FALSE, FALSE, 10);

    GtkWidget *grid = gtk_grid_new();

    gtk_container_add(GTK_CONTAINER(frame), grid);

    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);

    GtkWidget *labelNome = gtk_label_new("Nome:");
    GtkWidget *labelIdade = gtk_label_new("Idade:");

    entryNome = gtk_entry_new();
    entryIdade = gtk_entry_new();

    gtk_grid_attach(GTK_GRID(grid), labelNome, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entryNome, 1, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), labelIdade, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entryIdade, 1, 1, 1, 1);
}

void criarLista(GtkWidget *container) {

    GtkWidget *frame =
        gtk_frame_new("Lista de Pessoas");

    gtk_box_pack_start(GTK_BOX(container),
                       frame,
                       TRUE, TRUE, 10);

    listaPessoas = gtk_list_box_new();

    gtk_container_add(GTK_CONTAINER(frame),
                      listaPessoas);
}

//Função que irá executar após o click
void onClickAdicionarPessoa(GtkWidget *widget, gpointer data){
    const char *nome = gtk_entry_get_text(GTK_ENTRY(entryNome));
    const char *idadeStr = gtk_entry_get_text(GTK_ENTRY(entryIdade));

    if(strlen(nome) == 0){
        return;
    }

    adicionarPessoa(nome, atoi(idadeStr));

    atualizarLista();
}

void onClickEditarPessoa(GtkWidget *widget, gpointer data){
    GtkListBoxRow *row = gtk_list_box_get_selected_row(GTK_LIST_BOX(listaPessoas));

    if(row == NULL){
        return;
    }

    int indice = gtk_list_box_row_get_index(row);

    const char *nome = gtk_entry_get_text(GTK_ENTRY(entryNome));
    const char *idadeStr = gtk_entry_get_text(GTK_ENTRY(entryIdade));

    editarPessoa(indice, nome, atoi(idadeStr));

    atualizarLista();
}

void onClickRemoverPessoa(GtkWidget *widget, gpointer data){
    GtkListBoxRow *row = gtk_list_box_get_selected_row(GTK_LIST_BOX(listaPessoas));

    if(row == NULL){
        return;
    }

    int indice = gtk_list_box_row_get_index(row);

    removerPessoa(indice);

    atualizarLista();
}



void ativar(GtkApplication *app, gpointer data) {

    GtkWidget *janela =
        gtk_application_window_new(app);

    gtk_window_set_title(GTK_WINDOW(janela), "Sistema de Cadastro");

    gtk_window_set_default_size(GTK_WINDOW(janela),RESOLUCTION_X, RESOLUCTION_Y);

    GtkWidget *boxPrincipal = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    gtk_container_add(GTK_CONTAINER(janela), boxPrincipal);

    GtkWidget *labelTitulo =
        gtk_label_new("Cadastro de Pessoas");

    gtk_box_pack_start(GTK_BOX(boxPrincipal), labelTitulo, FALSE, FALSE, 5);

    criarCampos(boxPrincipal);
    criarBotoes(boxPrincipal);
    criarLista(boxPrincipal);

    atualizarLista();
    
    gtk_widget_show_all(janela);
}

