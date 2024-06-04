#ifndef TP_CPU_MAIN_H_
#define TP_CPU_MAIN_H_

#include <commons/log.h>
#include <commons/config.h>
#include <readline/readline.h>
#include "../../utils/include/utils.h"
#include "../../utils/include/conexiones.h"

t_log* logger;

t_instruccion* fetch(uint32_t PID, uint32_t PC, int socket_cpu_memoria);
t_instruccion* recibir_instruccion(int socket_cpu_memoria);

#endif //TP_CPU_MAIN_H_