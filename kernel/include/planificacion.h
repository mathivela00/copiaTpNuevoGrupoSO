//
// Created by mathi on 5/20/24.
//

#ifndef PLANIFICACION_H
#define PLANIFICACION_H

#include "../../utils/include/utils.h"
#include "../../utils/include/conexiones.h"
#include "recursos.h"

#include "extern_globales.h"

typedef  enum {
    FIFO,
    RR,
    ERROR
} t_algoritmo_planificacion;

sem_t proceso_new;
sem_t proceso_ready;
t_pcb* proceso_actual;

sem_t controlador_pcp;

t_algoritmo_planificacion algoritmo_utilizado;
t_list* planificador_corto_plazo;

t_contexto_ejecucion contexto_actual;




void* pcp_planificar(void* args);
void planificar_fifo();
void planificar_rr();

void cambiar_estado(t_pcb*, t_estado);

t_contexto_ejecucion* obtener_contexto_ejecucion(t_pcb*);
t_algoritmo_planificacion determinar_algoritmo();
t_pcb* modificar_pcb(t_pcb* proceso);

void* cronometrar(void* args);

#endif //PLANIFICACION_H
