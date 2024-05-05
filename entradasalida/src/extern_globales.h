#ifndef VARIABLES_GLOBALES_entradaSalida_H_
#define  VARIABLES_GLOBALES_entradaSalida_H_

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

extern char* TIPO_INTERFAZ;
extern int TIEMPO_UNIDAD_TRABAJO;
extern char* IP_KERNEL;
extern char* PUERTO_KERNEL;
extern char* IP_MEMORIA;
extern char* PUERTO_MEMORIA;
extern char* PATH_BASE_DIALFS;
extern int BLOCK_SIZE;
extern int BLOCK_COUNT;

extern t_log* logger_entradaSalida;
extern t_log* logger_entradaSalida_db;
extern t_config* entradaSalidaConfig;

extern int fd_memoria;
extern int fd_CPU;
extern int fd_kernel;
extern int fd_entradaSalida;




#endif /*  VARIABLES_GLOBALES_entradaSalida_H */
