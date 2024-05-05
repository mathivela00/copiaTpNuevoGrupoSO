#ifndef MEMORIA_H_
#define MEMORIA_H_

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
#include "inicioMemoria.h"
#include "extern_globales.h"
#include "Memoria-CPU.h"
#include "Memoria-Kernel.h"
#include "Memoria-EntradaSalida.h"

char* PUERTO_ESCUCHA;
int TAM_MEMORIA;
int TAM_PAGINA;
char* PATH_INSTRUCCIONES;
int RETARDO_RESPUESTA;


t_log* logger_memoria;
t_log* logger_memoria_db;
t_config* memoriaConfig;

int fd_memoria;
int fd_CPU;
int fd_kernel;
int fd_entradaSalida;





#endif /* MEMORIA_H */
