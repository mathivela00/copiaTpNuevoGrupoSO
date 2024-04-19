#include <stdlib.h>
#include <stdio.h>
#include <utils/utils.h>
#include <client.h>
#include <server.h>

char *leer_consola();

int main(int argc, char *argv[])
{
    /* ---------------- DEFINICION DE VARIABLES ---------------- */
    int conexion;
    
    int opcion_conexion; // 0 es recibir, 1 es enviar.
    int opcion_modulo;

    char *ip;
    char *valor;
    char *puerto_kernel;
    char *puerto_cpu;
    char *puerto_memoria;
    char *puerto_entrada_salida;

    /* ---------------- INICIALIZACION LOGGER ---------------- */
    t_log *logger;
    t_config *config;

    logger = iniciar_logger("kernel");
    if (logger == NULL)
    {
        printf("Error al iniciar el logger\n");
        return 1; // Salir con un código de error
    }
    log_info(logger, "Hola soy kernel");

    /* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */
    config = iniciar_config("../utils/cliente.config", logger);

    // Obtengo las variables
    ip = config_get_string_value(config, "IP");
    valor = config_get_string_value(config, "CLAVE");
    puerto_kernel = config_get_string_value(config, "PUERTO_KERNEL");
    puerto_cpu = config_get_string_value(config, "PUERTO_CPU");
    puerto_memoria = config_get_string_value(config, "PUERTO_MEMORIA");
    puerto_entrada_salida = config_get_string_value(config, "PUERTO_ENTRADA_SALIDA");

    // Loggeamos el valor de config
    log_info(logger, "Clave: %s", valor);
    log_info(logger, "IP Servidor: %s", ip);
    log_info(logger, "Puerto Kernel: %s", puerto_kernel);
    log_info(logger, "Puerto CPU: %s", puerto_cpu);
    log_info(logger, "Puerto Memoria: %s", puerto_memoria);
    log_info(logger, "Puerto Entrada/Salida: %s", puerto_entrada_salida);

    /* ---------------- LEER DE CONSOLA ---------------- */
    // lee consola hasta string vacio
    char *opcion;

    log_info(logger, "Quiere enviar o recibir?");
    while (1)
    {
        opcion = leer_consola();
        if (!strcmp(opcion, "enviar"))
        {
            opcion_conexion = 1;
            log_info(logger, "Elegiste ENVIAR. A cual modulo?");
            break;
        }
        else if (!strcmp(opcion, "recibir"))
        {
            opcion_conexion = 0;
            log_info(logger, "Elegiste RECIBIR.");
            break;
        }
        else
        {
            log_error(logger, "Ehh???");
        }
    }
    log_info(logger, "Opciones: cpu/memoria/io");
    free(opcion);
    if (opcion_conexion == 1)
    {
        while (1)
        {
            opcion = leer_consola();
            if (!strcmp(opcion, "cpu"))
            {
                log_info(logger, "Elegiste CPU.");
                opcion_modulo = puerto_cpu;
                break;
            }
            else if (!strcmp(opcion, "memoria"))
            {
                log_info(logger, "Elegiste MEMORIA");
                opcion_modulo = puerto_memoria;
                break;
            }
            else if (!strcmp(opcion, "io"))
            {
                log_info(logger, "Elegiste ENTRADA/SALIDA");
                opcion_modulo = puerto_entrada_salida;
                break;
            }
            else
            {
                log_error(logger, "Ehh???");
            }
        }
        free(opcion);
    }

    // opcion = leer_consola();

    /* ---------------- CREAR CONEXION COMO SERVIDOR ---------------- */
    if (opcion_conexion == 0) // Si elegimos RECIBIR
    {
        int server_fd = iniciar_servidor(puerto_kernel, logger);
        log_info(logger, "Servidor listo para recibir al cliente");

        int cliente_fd = esperar_cliente(server_fd, logger);
        int status = 0;
        while (1)
        {
            status = conexion_servidor(cliente_fd, logger);
            if (status == -1)
            {
                break;
            }
        }
    }

    /* ---------------- CREAR CONEXION COMO CLIENTE ---------------- */
    // Creamos una conexión hacia el servidor
    if (opcion_conexion == 1) // si elegimos ENVIAR
    {
        conexion = crear_conexion(ip, opcion_modulo);
        if (conexion == -1)
        {
            log_error(logger, "ERROR: No se pudo crear la conexion. Esta habilitado el servidor?");
            return EXIT_FAILURE;
        }

        // Enviamos al servidor el valor de CLAVE como mensaje
        enviar_mensaje(valor, opcion_modulo, logger);
    }

    // lee consola, Arma y envia el paquet
    // paquete(conexion, logger);

    terminar_programa(conexion, logger, config);

    return 0;
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

void terminar_programa(int conexion, t_log *logger, t_config *config)
{
    /* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config)
      con las funciones de las commons y del TP mencionadas en el enunciado */
    log_destroy(logger);
    config_destroy(config);
    liberar_conexion(conexion);
}

char *leer_consola()
{
    char *leido;
    leido = readline("> ");
    char *opcion = malloc(strlen(leido) + 1);
    strcpy(opcion, leido);
    free(leido);
    return opcion;
}