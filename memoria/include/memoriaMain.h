#ifndef TP_MEMORIA_MAIN_H_
#define TP_MEMORIA_MAIN_H_

#include <readline/readline.h>
#include <commons/bitarray.h>
#include "../../utils/include/utils.h"
#include "../../utils/include/conexiones.h"
#include "../include/memPaginacion.h"

// Conexiones
void conexion_con_cpu(int socket_cpu_memoria); 
void recibir_fetch(int socket_cpu_memoria, uint32_t* PID, uint32_t* PC);
void enviar_instruccion(int socket_cpu_memoria, t_instruccion* instruccion);


// memoria de instrucciones
t_instruccion* parsear_instruccion(char* linea);
t_list* leer_pseudocodigo(char* path);
cod_ins hash_ins(char* ins);
char* path_completo(char* path_base, char* path_parcial);
t_instruccion* get_ins(t_list* lista_instrucciones, uint32_t PC);
void fetch(int socket_cpu_memoria);

//LOGGER
extern t_log* logger;

//CONFIG
extern char* puerto_escucha;
extern char* path_base;
extern int tam_pagina;
extern int tam_memoria;
extern int retardo;
extern int cant_frames;

extern t_config* config;

void cargarConfig();

#endif //TP_MEMORIA_MAIN_H_