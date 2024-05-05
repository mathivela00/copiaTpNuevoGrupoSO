#ifndef KERNEL_H_
#define KERNEL_H_

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
#include "inicioKernel.h"
#include "extern_globales.h"
#include "Kernel-CPU-dispatch.h"
#include "Kernel-CPU-Interrupt.h"
#include "Kernel-Memoria.h"
#include "Kernel-EntradaSalida.h"

char* PUERTO_ESCUCHA;
char* IP_MEMORIA;
char* PUERTO_MEMORIA;
char* IP_CPU;
char* PUERTO_CPU_DISPATCH;
char* PUERTO_CPU_INTERRUPT;
char* ALGORITMO_PLANIFICACION;
int QUANTUM;
char** RECURSOS;
char** INSTANCIAS_RECURSOS;
char* GRADO_MULTIPROGRAMACION;

t_log* logger_kernel;
t_log* logger_kernel_db;
t_config* kernelConfig;

int fd_memoria;
int fd_CPU_dispatch;
int fd_CPU_interrupt;
int fd_kernel;
int fd_entradaSalida;










#endif /* MAIN_H_KERNEL */
