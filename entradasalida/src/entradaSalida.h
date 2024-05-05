#ifndef ENTRADA_SALIDA_H_
#define ENTRADA_SALIDA_H_

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

#include <utils/hello.h>
#include "inicioEntradaSalida.h"
#include "extern_globales.h"
#include "EntradaSalida-Memoria.h"
#include "EntradaSalida-Kernel.h"


char* TIPO_INTERFAZ;
int TIEMPO_UNIDAD_TRABAJO;
char* IP_KERNEL;
char* PUERTO_KERNEL;
char* IP_MEMORIA;
char* PUERTO_MEMORIA;
char* PATH_BASE_DIALFS;
int BLOCK_SIZE;
int BLOCK_COUNT;

t_log* logger_entradaSalida;
t_log* logger_entradaSalida_db;
t_config* entradaSalidaConfig;

int fd_memoria;
int fd_CPU;
int fd_kernel;
int fd_entradaSalida;


#endif /* ENTRADA_SALIDA_H_ */
