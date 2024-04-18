#include <stdlib.h>
#include <stdio.h>
#include <utils/utils.h>
#include <client.h>


int main(int argc, char *argv[])
{
    /* ---------------- DEFINICION DE VARIABLES ---------------- */
    int conexion_cpu;
    int conexion_memoria;
    int conexion_entrada_salida;

	char* ip;
	char* valor;
    char* puerto_cpu;
    char* puerto_memoria;
    char* puerto_entrada_salida;

    /* ---------------- INICIALIZACION LOGGER ---------------- */
    t_log *logger;
    t_config *config;

    logger = iniciar_logger("kernel");
    if (logger == NULL) {
        printf("Error al iniciar el logger\n");
        return 1; // Salir con un código de error
    }
    log_info(logger, "Hola soy kernel");


    /* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */
    config = iniciar_config("../utils/cliente.config", logger);

    // Obtengo las variables
    ip = config_get_string_value(config, "IP");
	valor = config_get_string_value(config, "CLAVE");
	puerto_cpu = config_get_string_value(config, "PUERTO_CPU");
    puerto_memoria = config_get_string_value(config, "PUERTO_MEMORIA");
    puerto_entrada_salida = config_get_string_value(config, "PUERTO_ENTRADA_SALIDA");

	// Loggeamos el valor de config
	log_info(logger, "Clave: %s", valor);
	log_info(logger, "IP Servidor: %s", ip);
	log_info(logger, "Puerto CPU: %s", puerto_cpu);
    log_info(logger, "Puerto Memoria: %s", puerto_memoria);
    log_info(logger, "Puerto Entrada/Salida: %s", puerto_entrada_salida);
    

    /* ---------------- LEER DE CONSOLA ---------------- */
    // lee consola hasta string vacio
    //leer_consola(logger);

    /* ---------------- CREAR CONEXION COMO CLIENTE ---------------- */  
    // Creamos una conexión hacia el servidor
	conexion_cpu = crear_conexion(ip, puerto_cpu);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor, conexion_cpu, logger);

	// lee consola, Arma y envia el paquete
	paquete(conexion_cpu, logger);

	terminar_programa(conexion_cpu, logger, config);

    return 0;
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
}


