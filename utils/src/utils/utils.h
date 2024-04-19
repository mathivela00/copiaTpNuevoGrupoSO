#ifndef UTILS_UTILS_H_
#define UTILS_UTILS_H_

#include <stdlib.h>
#include <stdio.h>
#include <commons/log.h>
#include <commons/string.h>
#include <commons/config.h>

/**
 * @fn    decir_hola
 * @brief Imprime un saludo al nombre que se pase por parámetro por consola.
 */
void decir_hola(char *quien);
t_log *iniciar_logger(char *nombre);
t_config *iniciar_config(char *archivo);
char *leer_consola();
void terminar_programa(int conexion, t_log *logger, t_config *config);
int enviar_o_recibir();

#endif
