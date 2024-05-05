#include "inicioEntradaSalida.h"

void iniciar_entradaSalida(){
    iniciar_logs();
	iniciar_configs();
	//imprimir_configs();


}

//-------------------------------------------FUNCIONES SECUNDARIAS PARA INICIAR MODULO-------------------------------------------------------//

void iniciar_logs()
{
	logger_entradaSalida= log_create("entradaSalida.log", "entradaSalida_LOG", true, LOG_LEVEL_INFO);
	if(logger_entradaSalida==NULL){
		perror("No se pudo crear el logger");
		exit(EXIT_FAILURE);
	}
	logger_entradaSalida_db= log_create("entradaSalida_DB.log", "entradaSalida_DB_LOG", true, LOG_LEVEL_TRACE);
	if(logger_entradaSalida_db==NULL){
		perror("No se pudo crear el logger");
		exit(EXIT_FAILURE);
	}
	
}

void iniciar_configs(){

	entradaSalidaConfig=config_create("entradaSalida.config");
	if(entradaSalidaConfig==NULL){
		perror("No se pudo crear la config");
		exit(EXIT_FAILURE);
	}

	TIPO_INTERFAZ=config_get_string_value(entradaSalidaConfig,"TIPO_INTERFAZ");
	TIEMPO_UNIDAD_TRABAJO=config_get_int_value(entradaSalidaConfig,"TIEMPO_UNIDAD_TRABAJO");
	IP_KERNEL=config_get_string_value(entradaSalidaConfig,"IP_KERNEL");
	PUERTO_KERNEL=config_get_string_value(entradaSalidaConfig,"PUERTO_KERNEL");
	IP_MEMORIA=config_get_string_value(entradaSalidaConfig,"IP_MEMORIA");
	PUERTO_MEMORIA=config_get_string_value(entradaSalidaConfig,"PUERTO_MEMORIA");
	PATH_BASE_DIALFS=config_get_string_value(entradaSalidaConfig,"PATH_BASE_DIALFS");
	BLOCK_SIZE=config_get_int_value(entradaSalidaConfig,"BLOCK_SIZE");
	BLOCK_COUNT=config_get_int_value(entradaSalidaConfig,"BLOCK_COUNT");



}	

void imprimir_configs(){
    
	log_info(logger_entradaSalida,"TIPO_INTERFAZ: %s",TIPO_INTERFAZ);
	log_trace(logger_entradaSalida_db,"TIEMPO_UNIDAD_TRABAJO : %i",TIEMPO_UNIDAD_TRABAJO);
	log_warning(logger_entradaSalida_db,"IP_KERNEL: %s", IP_KERNEL);


}