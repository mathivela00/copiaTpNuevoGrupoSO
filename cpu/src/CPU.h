#ifndef CPU_H_
#define CPU_H_

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
#include "inicioCPU.h"
#include "extern_globales.h"
#include "CPU-Kernel-dispatch.h"
#include "CPU-Kernel-Interrupt.h"
#include "CPU-Memoria.h"


char* PUERTO_ESCUCHA_DISPATCH;
char* PUERTO_ESCUCHA_INTERRUPT;
char* IP_MEMORIA;
char* PUERTO_MEMORIA;
int CANTIDAD_ENTRADAS_TLB;
char* ALGORITMO_TLB;

t_log* logger_CPU;
t_log* logger_CPU_db;
t_config* CPUConfig;

int fd_memoria;
int fd_CPU_dispatch;
int fd_CPU_interrupt;
int fd_kernel_dispatch;
int fd_kernel_interrupt;
int fd_entradaSalida;



#endif /* CPU_H */
