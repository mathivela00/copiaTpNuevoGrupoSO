#ifndef CPU_CICLOINSTRUCCION_H_
#define CPU_CICLOINSTRUCCION_H_

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
#include "extern_globales.h"

/* REGISTROS CPU */
uint32_t PC;    // Program Counter, indica la próxima instrucción a ejecutar
uint8_t AX;     // Registro Numérico de propósito general
uint8_t BX;     // Registro Numérico de propósito general
uint8_t CX;     // Registro Numérico de propósito general
uint8_t DX;     // Registro Numérico de propósito general
uint32_t EAX;   // Registro Numérico de propósito general
uint32_t EBX;   // Registro Numérico de propósito general
uint32_t ECX;   // Registro Numérico de propósito general
uint32_t EDX;   // Registro Numérico de propósito general
uint32_t SI;    // Contiene la dirección lógica de memoria de origen desde donde se va a copiar un string.
uint32_t DI;|   // Contiene la dirección lógica de memoria de destino a donde se va a copiar un string.

