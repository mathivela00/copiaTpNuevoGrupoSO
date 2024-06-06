//
// Created by mathi on 5/21/24.
//

#ifndef TPANUAL_RECURSOS_H
#define TPANUAL_RECURSOS_H
#include "../../utils/include/utils.h"
#include "../../utils/include/conexiones.h"
#include "planificacion.h"
#include <commons/collections/dictionary.h>
#include "extern_globales.h"

typedef struct
{
    int instancias;
    int n_recurso;
    t_list *bloqueados;
} t_recurso;

t_dictionary *dict_recursos;
char** config_recursos;
char** config_instancias_recursos;
int cantidad_recursos;

int obtener_cantidad_recursos(char** config_recursos);

void cargar_recursos(char** recursos, char** instancias_recursos, int cant_recursos);

void liberar_recursos(t_pcb* pcb, char** lista_recursos);



#endif //TPANUAL_RECURSOS_H
