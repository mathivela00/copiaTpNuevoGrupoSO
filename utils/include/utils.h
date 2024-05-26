#ifndef UTILS_HELLO_H_
#define UTILS_HELLO_H_

#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>

typedef enum 
{
    NUEVO,
    LISTO,
    EJECUCION,
    BLOQUEO,
    FINALIZADO
} t_estado;

typedef struct contexto_de_ejecucion_de_proceso
{
    uint32_t PC;
    uint8_t AX;
	uint8_t BX;
	uint8_t CX;
	uint8_t DX;
    uint32_t EAX;
    uint32_t EBX;
    uint32_t ECX;
    uint32_t EDX;
    uint32_t SI;
    uint32_t DI;
} t_contexto_ejecucion; 

typedef struct pcb_de_proceso
{
   	uint32_t PID;
    t_estado estado;
    uint32_t quantum;
    t_contexto_ejecucion CE;
} t_pcb;

//Funciones de Utils.
void decir_hola(char* );
void read_console(t_log *);
t_config *start_config(char* path);
t_log *start_logger(char* fileName, char* processName, t_log_level logLevel);
void end_program(t_log* logger, t_config* config);

#endif
