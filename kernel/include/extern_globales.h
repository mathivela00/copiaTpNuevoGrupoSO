#ifndef VARIABLES_GLOBALES_H_
#define  VARIABLES_GLOBALES_H_

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

#include "../../utils/include/utils.h"
#include "../../utils/include/conexiones.h"
#include "extern_globales.h"

 extern char* ip_memoria;
 extern char* puerto_memoria;
 extern char* ip_cpu;
 extern char* puerto_cpu_dispatch;
 extern char* puerto_cpu_interrupt;
 extern char* puerto_escucha;

extern int socket_kernel_cpu_dispatch;
extern int socket_kernel_cpu_interrupt; //queda libre por ahora
extern int socket_memoria_kernel;
extern int socket_entradasalida_kernel;
extern int socket_escucha;

extern t_log* logger;
extern t_log* logger_debug;
extern t_config* config;

extern int conexion_CPU_DISPATCH;
extern t_log* logger;
extern t_config *config;


/*
extern char* ALGORITMO_PLANIFICACION;
extern int QUANTUM;
extern char** RECURSOS;
extern char** INSTANCIAS_RECURSOS;
extern char* GRADO_MULTIPROGRAMACION;


*/






#endif /*  VARIABLES_GLOBALES */
