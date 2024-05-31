#ifndef TP_MEMORIA_MAIN_H_
#define TP_MEMORIA_MAIN_H_

#include <commons/log.h>
#include <commons/config.h>
#include <readline/readline.h>
#include "../../utils/include/utils.h"
#include "../../utils/include/conexiones.h"


// Conexiones
void conexion_con_cpu(int socket_cpu_memoria, t_list* lista_instrucciones);
void recibir_fetch(int socket_cpu_memoria, uint32_t* PID, uint32_t* PC);
void enviar_instruccion(int socket_cpu_memoria, t_instruccion* instruccion);



// memoria de instrucciones
t_instruccion* parsear_instruccion(char* linea);
t_list* leer_pseudocodigo(char* path);
cod_ins hash_ins(char* ins);
char* path_completo(char* path_base, char* path_parcial);
t_instruccion* get_ins(t_list* lista_instrucciones, uint32_t PC);


#endif //TP_MEMORIA_MAIN_H_