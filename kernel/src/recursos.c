/*
#include "../include/recursos.h"

int obtener_cantidad_recursos(char** config_recursos){
    int i = 0;
    while (config_recursos[i] != NULL)
    {
        i++;
    }
    return i;
}

void cargar_recursos(char** recursos, char** instancias_recursos, int cant_recursos){
    for (int i = 0; i<cant_recursos; i++)
    {
        t_recurso* rec = malloc(sizeof(t_recurso));
        rec->instancias = atoi(instancias_recursos[i]); //No se si funciona, es un char**
        rec->n_recurso = i;
        rec->bloqueados = list_create();

        dictionary_put(dict_recursos, recursos[i], rec);
    }
}

void liberar_recursos(t_pcb* pcb, char** lista_recursos)
{
    for (int i = 0; i < cantidad_recursos; i++)
    {
        t_recurso* rec = dictionary_get(dict_recursos, lista_recursos[i]);

        while (pcb->recursos_proceso[i] > 0)
        {
            rec->instancias += 1;
            pcb->recursos_proceso[i] -= 1;
        }

        dictionary_put(dict_recursos, lista_recursos[i], rec);
    }
}*/
