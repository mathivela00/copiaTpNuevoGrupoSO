#include "inicioCPU.h"

void iniciar_CPU(){
    iniciar_logs();
	iniciar_configs();
	//imprimir_configs();


}


//-------------------------------------------FUNCIONES SECUNDARIAS PARA INICIAR MODULO-------------------------------------------------------//


void iniciar_logs()
{
	logger_CPU= log_create("CPU.log", "CPU_LOG", true, LOG_LEVEL_INFO);
	if(logger_CPU==NULL){
		perror("No se pudo crear el logger");
		exit(EXIT_FAILURE);
	}
	logger_CPU_db= log_create("CPU_DB.log", "CPU_DB_LOG", true, LOG_LEVEL_TRACE);
	if(logger_CPU_db==NULL){
		perror("No se pudo crear el logger");
		exit(EXIT_FAILURE);
	}
	
}

void iniciar_configs(){

	CPUConfig=config_create("CPU.config");
	if(CPUConfig==NULL){
		perror("No se pudo crear la config");
		exit(EXIT_FAILURE);
	}

	PUERTO_ESCUCHA_DISPATCH=config_get_string_value(CPUConfig,"PUERTO_ESCUCHA_DISPATCH");
	PUERTO_ESCUCHA_INTERRUPT=config_get_string_value(CPUConfig,"PUERTO_ESCUCHA_INTERRUPT");
	IP_MEMORIA=config_get_string_value(CPUConfig,"IP_MEMORIA");
	PUERTO_MEMORIA=config_get_string_value(CPUConfig,"PUERTO_MEMORIA");
	CANTIDAD_ENTRADAS_TLB=config_get_int_value(CPUConfig,"CANTIDAD_ENTRADAS_TLB");
	ALGORITMO_TLB=config_get_string_value(CPUConfig,"ALGORITMO_TLB");

	

}

void imprimir_configs(){
    
	log_info(logger_CPU,"PUERTO_ESCUCHA_DISPATCH: %s",PUERTO_ESCUCHA_DISPATCH);
	log_warning(logger_CPU_db,"PUERTO_ESCUCHA_INTERRUPT: %s", PUERTO_ESCUCHA_INTERRUPT);
	log_trace(logger_CPU_db,"IP_MEMORIA: %s", IP_MEMORIA);
	log_trace(logger_CPU_db,"PUERTO_MEMORIA: %s", PUERTO_MEMORIA);
	log_trace(logger_CPU_db,"CANTIDAD_ENTRADAS_TLB: %i", CANTIDAD_ENTRADAS_TLB);


}