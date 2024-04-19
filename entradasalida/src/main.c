#include <stdlib.h>
#include <stdio.h>
#include <utils/utils.h>
#include <client.h>

int main(int argc, char *argv[])
{
    /* ---------------- DEFINICION DE VARIABLES ---------------- */

    int conexion;

    char *ip;
    char *valor;
    char *puerto_kernel;
    char *puerto_cpu;
    char *puerto_memoria;
    char *puerto_io;

    /* ---------------- INICIALIZACION LOGGER ---------------- */
    t_log *logger;
    t_config *config;

    logger = iniciar_logger("io");
    if (logger == NULL)
    {
        printf("Error al iniciar el logger\n");
        return 1; // Salir con un código de error
    }
    log_info(logger, "Hola soy io");

    /* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

    config = iniciar_config("../utils/cliente.config");
    // config_init(config,logger);

    // Obtengo las variables
    ip = config_get_string_value(config, "IP");
    valor = config_get_string_value(config, "CLAVE");
    puerto_kernel = config_get_string_value(config, "PUERTO_KERNEL");
    puerto_cpu = config_get_string_value(config, "PUERTO_CPU");
    puerto_memoria = config_get_string_value(config, "PUERTO_MEMORIA");
    puerto_io = config_get_string_value(config, "PUERTO_ENTRADA_SALIDA");

    // Loggeamos el valor de config
    log_info(logger, "Clave: %s", valor);
    log_info(logger, "IP Servidor: %s", ip);
    log_info(logger, "Puerto Kernel: %s", puerto_kernel);
    log_info(logger, "Puerto CPU: %s", puerto_cpu);
    log_info(logger, "Puerto Memoria: %s", puerto_memoria);
    log_info(logger, "Puerto Entrada/Salida: %s", puerto_io);

    /* ---------------- CREAR CONEXION COMO CLIENTE ---------------- */
    // Creamos una conexión hacia el servidor

    char *opcion;
    log_info(logger, "Quiere enviar a KERNEL o a MEMORIA?");
    while (1)
    {
        opcion = leer_consola();
        if (!strcmp(opcion, "kernel"))
        {
            log_info(logger, "Elegiste enviar al KERNEL");
            conexion = crear_conexion(ip, puerto_kernel);
            break;
        }
        else if (!strcmp(opcion, "memoria"))
        {
            log_info(logger, "Elegiste enviar a MEMORIA");
            conexion = crear_conexion(ip, puerto_memoria);
            break;
        }
        else
        {
            log_error(logger, "ERROR: Opcion invalida. Opciones: kernel/memoria");
        }
    }
    free(opcion);

    if (conexion == -1)
    {
        log_error(logger, "ERROR: No se pudo crear la conexion. Esta habilitado el servidor?");
        return EXIT_FAILURE;
    }

    // Enviamos al servidor el valor de CLAVE como mensaje
    enviar_mensaje(valor, conexion, logger);

    terminar_programa(conexion, logger, config);
    return EXIT_SUCCESS;

    // lee consola, Arma y envia el paquet
    // paquete(conexion, logger);

    return 0;
}
