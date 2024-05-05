#ifndef VARIABLES_GLOBALES_CPU_H_
#define  VARIABLES_GLOBALES_CPU_H_

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

extern char* PUERTO_ESCUCHA_DISPATCH;
extern char* PUERTO_ESCUCHA_INTERRUPT;
extern char* IP_MEMORIA;
extern char* PUERTO_MEMORIA;
extern int CANTIDAD_ENTRADAS_TLB;
extern char* ALGORITMO_TLB;

extern t_log* logger_CPU;
extern t_log* logger_CPU_db;
extern t_config* CPUConfig;

extern int fd_memoria;
extern int fd_CPU_dispatch;
extern int fd_CPU_interrupt;
extern int fd_kernel_dispatch;
extern int fd_kernel_interrupt;
extern int fd_entradaSalida;




#endif /*  VARIABLES_GLOBALES_CPU_H */
