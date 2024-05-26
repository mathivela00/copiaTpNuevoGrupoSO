#include "../include/memoriaMain.h"

int main(int argc, char* argv[]) {

    char* puerto_escucha;

    int socket_cpu_memoria;
    int socket_kernel_memoria;
    int socket_entradasalida_memoria;
    int socket_escucha;

    decir_hola("Memoria");

    //INSTANCIO LOGGER
    t_log* logger;
    //INICIALIZO LOGGER
    logger = start_logger("log_memoria.log", "LOG MEMORIA", LOG_LEVEL_INFO);

    //INSTACION CONFIG
    t_config* config;
    //INICIALIZO config
    config = start_config("./memoria.config");

    //Cargo y compruebo la config
    puerto_escucha = config_get_string_value(config, "PUERTO_ESCUCHA");
    log_info(logger, "PUERTO leido: %s", puerto_escucha);

    //iniciar Server de CPU
    socket_escucha = iniciar_servidor(puerto_escucha, logger);

    //esperar conexiones
    socket_cpu_memoria = esperar_cliente(socket_escucha, logger);
    socket_kernel_memoria = esperar_cliente(socket_escucha, logger);    
    socket_entradasalida_memoria = esperar_cliente(socket_escucha, logger);
    
    //Pruebas con CPU
    //enviar mensaje a cpu
    enviar_mensaje("MEMORIA manda mensaje a cpu", socket_cpu_memoria);
    log_info(logger, "Se envio el primer mensaje a cpu");

    //recibir respuesta de cpu
    op_code codop1 = recibir_operacion(socket_cpu_memoria);
    
    if (codop1 == MENSAJE) {log_info(logger, "LLego un mensaje");}
    else {log_info(logger, "LLego otra cosa");}
    recibir_mensaje(socket_cpu_memoria, logger);

    //Pruebas con kernel
    //enviar mensaje a kernel
    enviar_mensaje("MEMORIA manda mensaje a Kernel", socket_kernel_memoria);
    log_info(logger, "Se envio el primer mensaje a kernel");

    //recibir respuesta de kernel
    op_code codop2 = recibir_operacion(socket_kernel_memoria);
    
    if (codop2 == MENSAJE) {log_info(logger, "LLego un mensaje");}
    else {log_info(logger, "LLego otra cosa");}
    recibir_mensaje(socket_kernel_memoria, logger);

    //Pruebas con entradasalida
    //enviar mensaje a entradasalida
    enviar_mensaje("MEMORIA manda mensaje a entradasalida", socket_entradasalida_memoria);
    log_info(logger, "Se envio el primer mensaje a entradasalida");

    //recibir respuesta de entradasalida
    op_code codop3 = recibir_operacion(socket_entradasalida_memoria);
    
    if (codop3 == MENSAJE) {log_info(logger, "LLego un mensaje");}
    else {log_info(logger, "LLego otra cosa");}
    recibir_mensaje(socket_entradasalida_memoria, logger);

    if (socket_cpu_memoria) {liberar_conexion(socket_cpu_memoria);}
    if (socket_kernel_memoria) {liberar_conexion(socket_kernel_memoria);}
    if (socket_entradasalida_memoria) {liberar_conexion(socket_entradasalida_memoria);}
    if (socket_escucha) {liberar_conexion(socket_escucha);}

    return 0;
}
