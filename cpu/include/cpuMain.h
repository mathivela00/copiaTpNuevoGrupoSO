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
void ejecutar_instruccion(uint32_t PID, t_contexto_ejecucion* contexto_interno, t_instruccion* ins_actual);
void* direccion_registro(t_contexto_ejecucion* contexto, char* registro);
int tam_registro(char* registro);


#endif //TP_CPU_MAIN_H_