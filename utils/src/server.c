#include "server.h"

t_log *logger;

int iniciar_servidor(char* puerto, t_log *logger)
{
    int socket_servidor;

    struct addrinfo hints, *servinfo, *p;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, puerto, &hints, &servinfo);

    // Creamos el socket de escucha del servidor
    log_info(logger, "Creando socket de escucha");
    socket_servidor = socket(servinfo->ai_family,
                             servinfo->ai_socktype,
                             servinfo->ai_protocol);                    

    // Asociamos el socket a un puerto
    log_info(logger, "Asociando socket a un puerto...");
    
    if (bind(socket_servidor,
             servinfo->ai_addr,
             servinfo->ai_addrlen) != 0)
    {
        log_error(logger, "Error en el bind. Puede ser que haya dos instancias del mismo servidor activas.");
        exit(-1);
    }
    log_info(logger, "Espero conexiones de un cliente por el puerto %s", puerto);

    // Escuchamos las conexiones entrantes
    log_info(logger, "Escucho las conexiones entrantes");
    listen(socket_servidor, SOMAXCONN);

    freeaddrinfo(servinfo);
    log_trace(logger, "Listo para escuchar a mi cliente");

    return socket_servidor;
}

int esperar_cliente(int socket_servidor,t_log *logger)
{
    // Aceptamos un nuevo cliente
    log_info(logger, "Esperando conexion de cliente");
    int socket_cliente = accept(socket_servidor, NULL, NULL);
    if(socket_cliente == -1){
        log_error(logger,"ERROR: Error al aceptar el cliente.");
        return -1;
    }
    log_info(logger, "Se conecto un cliente!");

    return socket_cliente;
}

int recibir_operacion(int socket_cliente,t_log *logger)
{
	int cod_op;
	int32_t resultOk = 0;
	int32_t resultError = -1;

	if(recv(socket_cliente, &cod_op, sizeof(int), MSG_WAITALL) > 0){
		// Envio un mensaje de mensaje recibido correctamente
		printf("handshake ok\n");
		send(socket_cliente, &resultOk, sizeof(int32_t), 0);
		return cod_op;
	}else{
		// Envio un mensaje de mensaje recibido con fallas
		printf("handshake fallido\n");
		send(socket_cliente, &resultError, sizeof(int32_t), 0);
		close(socket_cliente);
		return -1;
	}
}

void *recibir_buffer(int *size, int socket_cliente)
{
    void *buffer;

    recv(socket_cliente, size, sizeof(int), MSG_WAITALL);
    buffer = malloc(*size);
    recv(socket_cliente, buffer, *size, MSG_WAITALL);

    return buffer;
}

void recibir_mensaje(int socket_cliente,t_log *logger)
{
    int size;
    char *buffer = recibir_buffer(&size, socket_cliente);
    log_info(logger, "Me llego el mensaje %s", buffer);
    free(buffer);
}

t_list* recibir_paquete(int socket_cliente,t_log *logger)
{
	int size;
	int desplazamiento = 0;
	void * buffer;
	t_list* valores = list_create();
	int tamanio;

	buffer = recibir_buffer(&size, socket_cliente);
	while(desplazamiento < size)
	{
		memcpy(&tamanio, buffer + desplazamiento, sizeof(int));
		desplazamiento+=sizeof(int);
		char* valor = malloc(tamanio);
		memcpy(valor, buffer+desplazamiento, tamanio);
		desplazamiento+=tamanio;
		list_add(valores, valor);
	}
	free(buffer);
	return valores;
}

int conexion_servidor(int cliente, t_log *logger)
{
    t_list *lista;
    int cod_op = recibir_operacion(cliente, logger);
    switch (cod_op)
    {
    case MENSAJE:
        recibir_mensaje(cliente, logger);
        return 2;
    case PAQUETE:
        lista = recibir_paquete(cliente, logger);
        log_info(logger, "Me llegaron los siguientes valores:\n");
        // no lo puedo usar por que no me detecta el logger
        // list_iterate(lista, (void*) iterator);

        for (int i = 0; i < list_size(lista); i++)
        {
            char *elemento = list_get(lista, i);
            log_info(logger, "%s", elemento);
        }

        return 1;
    case -1:
        log_error(logger, "el cliente se desconecto. Terminando servidor");
        return -1;
    default:
        log_warning(logger, "Operacion desconocida. No quieras meter la pata");
        return 0;
    }
}