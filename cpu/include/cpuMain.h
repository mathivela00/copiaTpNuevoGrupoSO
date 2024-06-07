#ifndef TP_CPU_MAIN_H_
#define TP_CPU_MAIN_H_

#include <commons/log.h>
#include <commons/config.h>
#include <readline/readline.h>
#include "../../utils/include/utils.h"
#include "../../utils/include/conexiones.h"

t_log* logger;
int_code interrupcion;

char* ip_memoria;
char* puerto_memoria;
char* puerto_escucha_dispatch;
char* puerto_escucha_interrupt;

int socket_cpu_kernel_dispatch;
int socket_cpu_kernel_interrupt;
int socket_cpu_memoria;
int socket_escucha;

t_instruccion* fetch(uint32_t PID, uint32_t PC, int socket_cpu_memoria);
t_instruccion* recibir_instruccion(int socket_cpu_memoria);
void ejecutar_instruccion(uint32_t PID, t_contexto_ejecucion* contexto_interno, t_instruccion* ins_actual);
void* direccion_registro(t_contexto_ejecucion* contexto, char* registro);
int tam_registro(char* registro);
bool check_interrupt(int_code interrupcion, uint32_t PID, t_contexto_ejecucion contexto_interno);
void recibir_proceso(int socket_cpu_kernel_dispatch, uint32_t* PID, t_contexto_ejecucion* contexto_interno);




#endif //TP_CPU_MAIN_H_