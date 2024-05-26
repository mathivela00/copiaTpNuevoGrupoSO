#include "../include/kernelMain.h"

int main(int argc, char* argv[]) {

    char* ip_memoria;
    char* puerto_memoria;
    char* ip_cpu;
    char* puerto_cpu_dispatch;
    char* puerto_cpu_interrupt;
    char* puerto_escucha;

    int socket_kernel_cpu_dispatch;
    int socket_kernel_cpu_interrupt; //queda libre por ahora
    int socket_memoria_kernel;
    int socket_entradasalida_kernel;
    int socket_escucha;

    decir_hola("Kernel");

    //INSTANCIO LOGGER
    t_log* logger;
    //INICIALIZO LOGGER
    logger = start_logger("log_kernel.log", "LOG KERNEL", LOG_LEVEL_INFO);

    //INSTACION CONFIG
    t_config* config;
    //INICIALIZO config
    config = start_config("./kernel.config");

    ip_cpu = config_get_string_value(config, "IP_CPU");
    puerto_cpu_dispatch = config_get_string_value(config, "PUERTO_CPU_DISPATCH");
    puerto_cpu_interrupt = config_get_string_value(config, "PUERTO_CPU_INTERRUPT");
    ip_memoria = config_get_string_value(config, "IP_MEMORIA");
    puerto_memoria = config_get_string_value(config, "PUERTO_MEMORIA");
    puerto_escucha = config_get_string_value(config, "PUERTO_ESCUCHA");

    //Pruebas con memoria
    //Conectar con el server memoria
    socket_memoria_kernel = crear_conexion(ip_memoria, puerto_memoria);
    //Recibir un mensaje de memoria
    op_code codop = recibir_operacion(socket_memoria_kernel);
    if (codop == MENSAJE) {printf("LLego un mensaje\n");}
    else {printf("LLego otra cosa");}
    recibir_mensaje(socket_memoria_kernel, logger);

    //Enviar un mensaje a memoria
    enviar_mensaje("Kernel manda mensaje a memoria", socket_memoria_kernel);
    log_info(logger, "Se envio el primer mensaje a memoria");

    //Pruebas con CPU
    //Conectar con el server CPU
    socket_kernel_cpu_dispatch = crear_conexion(ip_cpu, puerto_cpu_dispatch);

    //Recibir un mensaje de CPU
    op_code codop1 = recibir_operacion(socket_kernel_cpu_dispatch);
    if (codop1 == MENSAJE) {printf("LLego un mensaje\n");}
    else {printf("LLego otra cosa");}
    recibir_mensaje(socket_kernel_cpu_dispatch, logger);

    //Enviar un mensaje a CPU
    enviar_mensaje("Kernel manda mensaje a CPU", socket_kernel_cpu_dispatch);
    log_info(logger, "Se envio el primer mensaje a CPU");

    //Pruebas con entradasalida
    //iniciar Server de kernel
    socket_escucha = iniciar_servidor(puerto_escucha, logger);

    //esperar conexion de entradasalida
    socket_entradasalida_kernel = esperar_cliente(socket_escucha, logger);

    //enviar mensaje a entradasalida
    enviar_mensaje("kernel manda mensaje a entradasalida", socket_entradasalida_kernel);
    log_info(logger, "Se envio el primer mensaje a entradasalida");

    //recibir respuesta de entradasalida
    op_code codop2 = recibir_operacion(socket_entradasalida_kernel);    
    if (codop2 == MENSAJE) {log_info(logger, "LLego un mensaje");}
    else {log_info(logger, "LLego otra cosa");}
    recibir_mensaje(socket_entradasalida_kernel, logger);

    if (socket_kernel_cpu_dispatch) {liberar_conexion(socket_kernel_cpu_dispatch);}
    if (socket_kernel_cpu_interrupt) {liberar_conexion(socket_kernel_cpu_interrupt);}
    if (socket_memoria_kernel) {liberar_conexion(socket_memoria_kernel);}
    if (socket_entradasalida_kernel) {liberar_conexion(socket_entradasalida_kernel);}
    if (socket_escucha) {liberar_conexion(socket_escucha);}
    return 0;
}
