#ifndef SERVICIOS_KERNEL_H_
#define SERVICIOS_KERNEL_H_


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


#include "extern_globales.h"


int identificador_PID =1;
pthread_mutex_t mutex_pid;

int asignar pid();









#endif /*  SERVICIOS_KERNEL_H_ */
