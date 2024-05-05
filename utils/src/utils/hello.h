#ifndef UTILS_H_
#define UTILS_H_

#include <stdlib.h>
#include <stdio.h>
#include<signal.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include <pthread.h>

typedef enum
{
	MENSAJE,
	PAQUETE,
	HANDSHAKE,
	//KERNEL MEMORIA------
	CREAR_PROCESO_KM,
	RPTA_CREAR_PROCESO_MK,
	//KERNEL CPU-----

	//KERNEL I/O

	// I/O  MEMORIA ------

	// CPU  MEMORIA
}op_code;

typedef struct
{
	int size;
	void* stream;
} t_buffer;

typedef struct
{
	op_code codigo_operacion;
	t_buffer* buffer;
} t_paquete;





void paquete(int conexion);
void terminar_programa(int , t_log* , t_config* );
void list_logger(t_list* list,t_log*);

// Funciones Servidor
int iniciar_servidor(char*,t_log*,char* );
//void iterator(char* ,t_log*);
int esperar_cliente(int ,t_log*,char* );
t_list* recibir_paquete(int);
void recibir_mensaje(int ,t_log*);
int recibir_operacion(int);

//Funciones cliente
int crear_conexion(char* ip, char* puerto);
void enviar_mensaje(char* mensaje, int socket_cliente);
t_paquete* crear_paquete(void);
void agregar_a_paquete(t_paquete* paquete, void* valor, int tamanio);
void enviar_paquete(t_paquete* paquete, int socket_cliente);
void liberar_conexion(int socket_cliente);
void eliminar_paquete(t_paquete* paquete);










#endif /* UTILS_HELLO_H_ */
