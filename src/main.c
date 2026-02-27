#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "model.h"
#include "view.h"

int main(int argc, char **argv){
    // =========================
    // 0 - Inicializando o banco
    // =========================

    inicializarBanco();

    // =========================
    // 1 - Criar Aplicação GTK
    // =========================
    GtkApplication *app = gtk_application_new( "com.crudvisual.cadastro",G_APPLICATION_DEFAULT_FLAGS);

    // =========================
    // 2 - Conectar Evento Activate
    // =========================

    g_signal_connect( app, "activate", G_CALLBACK(ativar), NULL);

    // =========================
    // 3 - Iniciar Loop GTK
    // =========================

    int status = g_application_run(G_APPLICATION(app),argc,argv);

    // =========================
    // 4 - Liberar Memória
    // =========================
    g_object_unref(app);

    return status;
}

