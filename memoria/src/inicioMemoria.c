#include "inicioMemoria.h"

void iniciar_memoria(){
    iniciar_logs();
	iniciar_configs();
	//imprimir_configs();


}


//-------------------------------------------FUNCIONES SECUNDARIAS PARA INICIAR MODULO-------------------------------------------------------//



void iniciar_logs()
{
	logger_memoria= log_create("memoria.log", "memoria_LOG", true, LOG_LEVEL_INFO);
	if(logger_memoria==NULL){
		perror("No se pudo crear el logger");
		exit(EXIT_FAILURE);
	}
	logger_memoria_db= log_create("memoria_DB.log", "memoria_DB_LOG", true, LOG_LEVEL_TRACE);
	if(logger_memoria_db==NULL){
		perror("No se pudo crear el logger");
		exit(EXIT_FAILURE);
	}
	
}

void iniciar_configs(){

	memoriaConfig=config_create("memoria.config");
	if(memoriaConfig==NULL){
		perror("No se pudo crear la config");
		exit(EXIT_FAILURE);
	}

	PUERTO_ESCUCHA=config_get_string_value(memoriaConfig,"PUERTO_ESCUCHA");
	TAM_MEMORIA=config_get_int_value(memoriaConfig,"TAM_MEMORIA");
	TAM_PAGINA=config_get_int_value(memoriaConfig,"TAM_PAGINA");
	PATH_INSTRUCCIONES=config_get_string_value(memoriaConfig,"PATH_INSTRUCCIONES");
	RETARDO_RESPUESTA=config_get_int_value(memoriaConfig,"RETARDO_RESPUESTA");

}	

void imprimir_configs(){
    
	log_info(logger_memoria,"PUERTO_ESCUCHA: %s",PUERTO_ESCUCHA);
	log_trace(logger_memoria_db,"TAM_MEMORIA : %i",TAM_MEMORIA);
	log_warning(logger_memoria_db,"PATH_INSTRUCCIONES: %s", PATH_INSTRUCCIONES);


}