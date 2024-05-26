#ifndef CONEXIONES_TP_H_
#define CONEXIONES_TP_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <readline/readline.h>
#include <commons/log.h>
#include <commons/collections/list.h>
#include "utils.h"

/*----------Estructuras----------*/

typedef enum CODIGOS_DE_OPERACIONES
{
    MENSAJE,
    PAQUETE,
    CE
} op_code;

typedef struct
{
    uint32_t size;
    void* stream;
} t_buffer;

typedef struct
{
    op_code codigo_operacion;
    t_buffer* buffer;
} t_paquete;

/*----------Fin Estructuras----------*/

/*----------Cliente----------*/

int crear_conexion(char* ip, char* puerto);
void liberar_conexion(int socket_cliente);

/*----------Fin Cliente----------*/

/*----------Servidor----------*/

int iniciar_servidor(char* puerto_escucha, t_log* logger);
int esperar_cliente(int socket, t_log* logger);

/*----------Fin Servidor----------*/

/*----------Mensajeria----------*/
void enviar_mensaje(char* mensaje, int socket);
t_paquete* crear_paquete(op_code codigo);
void crear_buffer(t_paquete* paquete);
void agregar_a_paquete(t_paquete* paquete, void* valor, int tamanio);
void enviar_paquete(t_paquete* paquete, int socket);
void eliminar_paquete(t_paquete* paquete);
void* serializar_paquete(t_paquete* paquete, int bytes);

op_code recibir_operacion(int socket);
t_list* recibir_paquete(int socket);
void recibir_mensaje(int socket, t_log* logger);
void* recibir_buffer(uint32_t* size, int socket);

void enviar_CE(int socket, uint32_t PID, t_contexto_ejecucion contexto);
void recibir_CE(int socket, uint32_t PID, t_contexto_ejecucion contexto_contenedor);
/*----------Fin Mensajeria----------*/


/*----------Serializacion----------*/
void agregar_a_paquete_uint8(t_paquete* paquete, uint8_t numero);
void agregar_a_paquete_uint32(t_paquete* paquete, uint32_t numero);
void agregar_a_paquete_string(t_paquete* paquete, uint32_t tamanio, char* string);

uint8_t leer_de_buffer_uint8(void* buffer, int* desplazamiento);
uint32_t leer_de_buffer_uint32(void* buffer, int* desplazamiento);
char* leer_de_buffer_string(void* buffer, int* desplazamiento);

void serializar_CE(t_paquete* paquete, t_contexto_ejecucion contexto);

/*----------Fin Serializacion----------*/


#endif //CONEXIONES_TP_H_
