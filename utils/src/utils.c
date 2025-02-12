#include "../include/utils.h"
#include <commons/config.h>
#include <commons/log.h>
#include <readline/readline.h>

void decir_hola(char* quien) {
    printf("Estassss %s ON!!\n", quien);
}

void read_console(t_log *logger) {
    char* readed;
    readed = readline(">> ");
    log_info(logger, ">> %s", readed);

    while (strcmp(readed, "")!=0) {
        free(readed);
        readed = readline(">> ");
        log_info(logger, ">> %s", readed);
    };
    free(readed);
}

t_config *start_config(char* path) {
    t_config* new_config = config_create(path);
    if(new_config == NULL){
        perror("Error al cargar la configuracion de la CPU.");
        exit(EXIT_FAILURE);
    }

    return new_config;
}

t_log *start_logger( char* fileName, char* processName, t_log_level logLevel) {
    t_log* new_logger = log_create( fileName,  processName, 1, logLevel);
    if(new_logger == NULL){
        perror("Error al crear el Log.");
        exit(EXIT_FAILURE);
    }
    return new_logger;
}


void end_program(t_log* logger, t_config* config)
{
    /* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config)
      con las funciones de las commons y del TP mencionadas en el enunciado */
    log_destroy(logger);
    config_destroy(config);
}



