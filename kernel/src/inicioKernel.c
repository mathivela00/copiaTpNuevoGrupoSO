#include "../include/inicioKernel.h"


void iniciar_Kernel(){
    iniciar_logs();
	iniciar_configs();
	//imprimir_configs();


}


//-------------------------------------------FUNCIONES SECUNDARIAS PARA INICIAR MODULO-------------------------------------------------------//


void iniciar_logs()
{
	logger = start_logger("log_kernel.log", "LOG KERNEL", LOG_LEVEL_INFO);
	if(logger==NULL){
		perror("No se pudo crear el logger");
		exit(EXIT_FAILURE);
	}
	logger_debug= log_create("kernel_DB.log", "KERNEL_DB_LOG", true, LOG_LEVEL_TRACE);
	if(logger_debug==NULL){
		perror("No se pudo crear el logger debug");
		exit(EXIT_FAILURE);
	}
	
}

void iniciar_configs(){

	config = start_config("./kernel.config");
	if(config==NULL){
		perror("No se pudo crear la config");
		exit(EXIT_FAILURE);
	}

    ip_cpu = config_get_string_value(config, "IP_CPU");
    puerto_cpu_dispatch = config_get_string_value(config, "PUERTO_CPU_DISPATCH");
    puerto_cpu_interrupt = config_get_string_value(config, "PUERTO_CPU_INTERRUPT");
    ip_memoria = config_get_string_value(config, "IP_MEMORIA");
    puerto_memoria = config_get_string_value(config, "PUERTO_MEMORIA");
    puerto_escucha = config_get_string_value(config, "PUERTO_ESCUCHA");
	
/*	ALGORITMO_PLANIFICACION=config_get_string_value(kernelConfig,"ALGORITMO_PLANIFICACION");
	QUANTUM=config_get_int_value(kernelConfig,"QUANTUM");
	RECURSOS=config_get_array_value(kernelConfig,"RECURSOS");
	INSTANCIAS_RECURSOS=config_get_array_value(kernelConfig,"INSTANCIAS_RECURSOS");
	GRADO_MULTIPROGRAMACION=config_get_string_value(kernelConfig,"GRADO_MULTIPROGRAMACION");
*/
}

