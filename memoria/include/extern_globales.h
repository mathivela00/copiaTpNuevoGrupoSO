#ifndef VARIABLES_GLOBALES_MEMORIA_H_
#define  VARIABLES_GLOBALES_MEMORIA_H_

#include <stdlib.h>
#include <stdio.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <pthread.h>

#include <semaphore.h>
#include <commons/collections/queue.h>


#include "../../utils/include/utils.h"
#include "../../utils/include/conexiones.h"


extern t_log* logger;
extern char* path_base;
extern int tam_pagina;
extern int tam_memoria;
extern int retardo;

extern char* puerto_escucha;
extern int socket_cpu_memoria;
extern int socket_kernel_memoria;
extern int socket_entradasalida_memoria;
extern int socket_escucha;


///////////////////////////////////

extern char* PUERTO_ESCUCHA;
//extern int TAM_MEMORIA;
//extern int TAM_PAGINA;
//extern char* PATH_INSTRUCCIONES;
//extern int RETARDO_RESPUESTA;


//extern t_log* logger_memoria;
//extern t_log* logger_memoria_db;
//extern t_config* memoriaConfig;

extern int fd_memoria;
extern int fd_CPU;
extern int fd_kernel;
extern int fd_entradaSalida;




#endif /*  VARIABLES_GLOBALES_MEMORIA_H */
