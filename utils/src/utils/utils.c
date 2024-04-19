#include <utils/utils.h>
#include <commons/txt.h>
#include <readline/readline.h>

void decir_hola(char *quien)
{
    printf("Hola desde %s!!\n", quien);
}

t_log *iniciar_logger(char *nombre)
{
    // Creando el nombre del archivo
    char *archivo = malloc(strlen(nombre) + strlen(".log") + 1);
    strcpy(archivo, nombre);
    strcat(archivo, ".log");

    t_log *nuevo_logger = log_create(archivo, nombre, true, LOG_LEVEL_INFO);

    return nuevo_logger;
}

t_config *iniciar_config(char *archivo)
{
    t_config *nuevo_config;

    // Crear la nueva configuración.
    nuevo_config = config_create(archivo);

    return nuevo_config;
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

void terminar_programa(int conexion, t_log *logger, t_config *config)
{
    /* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config)
      con las funciones de las commons y del TP mencionadas en el enunciado */
    log_destroy(logger);
    config_destroy(config);
    liberar_conexion(conexion);
}
