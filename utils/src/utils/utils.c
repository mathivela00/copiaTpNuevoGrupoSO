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

t_config *iniciar_config(char *archivo, t_log* logger)
{
    t_config* nuevo_config;

    // Crear la nueva configuración.
    nuevo_config = config_create(archivo);

    return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// Leo la primera linea
	leido = readline("> ");
	// Itero hasta que se ingrese un string vacio
	while(strcmp(leido, "") > 0){
		log_info(logger, leido);
		leido = readline("> ");
	}

	// Libero memoria
	free(leido);
}
