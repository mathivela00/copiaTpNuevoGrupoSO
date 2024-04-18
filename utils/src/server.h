#ifndef SERVER_H_
#define SERVER_H_

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netdb.h>
#include<commons/log.h>
#include<commons/collections/list.h>
#include<string.h>
#include<assert.h>

#define PUERTO "4444"

/* comento ya que lo obtiene desde cliente
typedef enum
{
	MENSAJE,
	PAQUETE
}op_code;
*/

extern t_log* logger;

void* recibir_buffer(int*, int);

int iniciar_servidor(char* puerto, t_log* logger);
int esperar_cliente(int,t_log* logger);
t_list* recibir_paquete(int,t_log* logger);
void recibir_mensaje(int,t_log* logger);
int recibir_operacion(int,t_log* logger);

#endif /* UTILS_H_ */