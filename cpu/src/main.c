#include <main.h>


int main(int argc, char *argv[])
{
    /* ---------------- DEFINICION DE VARIABLES ---------------- */
    int conexion_kernel;
    int conexion_memoria;
    int conexion_entrada_salida;

	char* ip;
	char* valor;
    char* puerto_kernel;
    char* puerto_cpu;
    char* puerto_memoria;
    char* puerto_entrada_salida;

    /* ---------------- INICIALIZACION LOGGER ---------------- */
    t_log *logger;
    t_config *config;

    logger = iniciar_logger("cpu");
    if (logger == NULL) {
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
    //leer_consola(logger);

    /* ---------------- CREAR CONEXION COMO CLIENTE ---------------- */
    // Creamos una conexión hacia el servidor
	conexion_kernel = crear_conexion(ip, puerto_kernel);
    if (conexion_kernel == -1){
        log_error(logger, "ERROR: No se pudo crear la conexion. Esta habilitado el servidor?");
        return EXIT_FAILURE;
    }

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor, conexion_kernel, logger);  


    /* ---------------- CREAR CONEXION COMO SERVIDOR ---------------- */
	int server_fd = iniciar_servidor(puerto_cpu, logger);
	log_info(logger, "Servidor listo para recibir al cliente");
    
	int cliente_fd = esperar_cliente(server_fd, logger);
    
	t_list* lista;
	while (1) {
		int cod_op = recibir_operacion(cliente_fd, logger);
		switch (cod_op) {
		case MENSAJE:
			recibir_mensaje(cliente_fd, logger);
			break;
		case PAQUETE:
			lista = recibir_paquete(cliente_fd, logger);
			log_info(logger, "Me llegaron los siguientes valores:\n");
            // no lo puedo usar por que no me detecta el logger
			//list_iterate(lista, (void*) iterator);

            for (int i = 0; i < list_size(lista); i++) {
                char* elemento = list_get(lista, i);
                log_info(logger, "%s", elemento);
            }

			break;
		case -1:
			log_error(logger, "el cliente se desconecto. Terminando servidor");
			return EXIT_FAILURE;
		default:
			log_warning(logger,"Operacion desconocida. No quieras meter la pata");
			break;
		}
	}

    terminar_programa(server_fd, logger, config);    

    return EXIT_SUCCESS;
}

void iterator(char* value) {
	log_info(logger,"%s", value);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
}

