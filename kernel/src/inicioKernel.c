#include "inicioKernel.h"

void iniciar_Kernel(){
    iniciar_logs();
	iniciar_configs();
	//imprimir_configs();


}


//-------------------------------------------FUNCIONES SECUNDARIAS PARA INICIAR MODULO-------------------------------------------------------//



void iniciar_logs()
{
	logger_kernel= log_create("kernel.log", "KERNEL_LOG", true, LOG_LEVEL_INFO);
	if(logger_kernel==NULL){
		perror("No se pudo crear el logger");
		exit(EXIT_FAILURE);
	}
	logger_kernel_db= log_create("kernel_DB.log", "KERNEL_DB_LOG", true, LOG_LEVEL_TRACE);
	if(logger_kernel_db==NULL){
		perror("No se pudo crear el logger");
		exit(EXIT_FAILURE);
	}
	
}

void iniciar_configs(){

	kernelConfig=config_create("kernel.config");
	if(kernelConfig==NULL){
		perror("No se pudo crear la config");
		exit(EXIT_FAILURE);
	}
	PUERTO_ESCUCHA=config_get_string_value(kernelConfig,"PUERTO_ESCUCHA");
	IP_MEMORIA=config_get_string_value(kernelConfig,"IP_MEMORIA");
	PUERTO_MEMORIA=config_get_string_value(kernelConfig,"PUERTO_MEMORIA");
	IP_CPU=config_get_string_value(kernelConfig,"IP_CPU");
	PUERTO_CPU_DISPATCH=config_get_string_value(kernelConfig,"PUERTO_CPU_DISPATCH");
	PUERTO_CPU_INTERRUPT=config_get_string_value(kernelConfig,"PUERTO_CPU_INTERRUPT");
	ALGORITMO_PLANIFICACION=config_get_string_value(kernelConfig,"ALGORITMO_PLANIFICACION");
	QUANTUM=config_get_int_value(kernelConfig,"QUANTUM");
	RECURSOS=config_get_array_value(kernelConfig,"RECURSOS");
	INSTANCIAS_RECURSOS=config_get_array_value(kernelConfig,"INSTANCIAS_RECURSOS");
	GRADO_MULTIPROGRAMACION=config_get_string_value(kernelConfig,"GRADO_MULTIPROGRAMACION");

}

void imprimir_configs(){
	log_info(logger_kernel,"PUERTO_ESCUCHA: %s",PUERTO_ESCUCHA);
	log_warning(logger_kernel_db,"IP MEMORIA: %s", IP_MEMORIA);
	log_trace(logger_kernel_db,"PUERTO MEMORIA: %s", PUERTO_MEMORIA);
	log_trace(logger_kernel_db,"RECURSOS: %s|%s|%s", RECURSOS[0],RECURSOS[1],RECURSOS[2]);
	log_trace(logger_kernel_db,"INSTANCIAS RECURSOS: %s --%s -- %s", INSTANCIAS_RECURSOS[0],INSTANCIAS_RECURSOS[1],INSTANCIAS_RECURSOS[2]);


}

