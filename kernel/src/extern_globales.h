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



#include <utils/hello.h>
extern char* PUERTO_ESCUCHA;
extern char* IP_MEMORIA;
extern char* PUERTO_MEMORIA;
extern char* IP_CPU;
extern char* PUERTO_CPU_DISPATCH;
extern char* PUERTO_CPU_INTERRUPT;
extern char* ALGORITMO_PLANIFICACION;
extern int QUANTUM;
extern char** RECURSOS;
extern char** INSTANCIAS_RECURSOS;
extern char* GRADO_MULTIPROGRAMACION;
extern t_log* logger_kernel;
extern t_log* logger_kernel_db;
extern t_config* kernelConfig;

extern int fd_memoria;
extern int fd_CPU_dispatch;
extern int fd_CPU_interrupt;
extern int fd_kernel;
extern int fd_entradaSalida;






#endif /*  VARIABLES_GLOBALES */
