#include <main.h>

int main(int argc, char *argv[])
{
    /* ---------------- DEFINICION DE VARIABLES ---------------- */
    int conexion_memoria;
    int opcion_conexion = -1;        // 0 es recibir, 1 es enviar. -1 es default

    char *ip;
    char *valor;
    char *puerto_kernel;
    char *puerto_cpu;
    char *puerto_memoria;
    char *puerto_io;

    /* ---------------- INICIALIZACION LOGGER ---------------- */
    t_log *logger;
    t_config *config;

    logger = iniciar_logger("cpu");
    if (logger == NULL)
    {
        printf("Error al iniciar el logger\n");
        return 1; // Salir con un código de error
    }
    log_info(logger, "Hola soy cpu");

    /* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */
    config = iniciar_config("../utils/cliente.config");

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

    /* ---------------- LEER DE CONSOLA ---------------- */

    log_info(logger, "Quiere enviar a MEMORIA o recibir del KERNEL?");
    while (opcion_conexion == -1)
    {
        opcion_conexion = enviar_o_recibir();
        if (opcion_conexion == -1)
        {
            log_error(logger, "ERROR: Opcion invalida. Escriba 'enviar' o 'recibir'");
        }
    }

    if (opcion_conexion == 1)
    {
        log_info(logger, "Elegiste enviar a MEMORIA");
        /* ---------------- CREAR CONEXION COMO CLIENTE CON EL MODULO DE MEMORIA ---------------- */
        // Creamos una conexión hacia el modulo de memoria
        conexion_memoria = crear_conexion(ip, puerto_memoria);
        if (conexion_memoria == -1)
        {
            log_error(logger, "ERROR: No se pudo crear la conexion. Esta habilitado el módulo de Memoria?");
            return EXIT_FAILURE;
        }

        // Enviamos al modulo de memoria el valor de CLAVE como mensaje
        enviar_mensaje(valor, conexion_memoria, logger);
        terminar_programa(conexion_memoria, logger, config);
        return EXIT_SUCCESS;   
    }
    else
    {
        log_info(logger, "Elegiste recibir del KERNEL");

        /* ---------------- CREAR CONEXION COMO SERVIDOR CON EL MODULO DE KERNEL ---------------- */
        int server_fd = iniciar_servidor(puerto_cpu, logger);
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

        terminar_programa(server_fd, logger, config);
        return EXIT_SUCCESS;    
    }

    
}

void iterator(char *value)
{
    log_info(logger, "%s", value);
}
