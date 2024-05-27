#include "../include/cpuMain.h"

int main(int argc, char* argv[]) {

    char* ip_memoria;
    char* puerto_memoria;
    char* puerto_escucha_dispatch;
    char* puerto_escucha_interrupt;

    int socket_cpu_kernel_dispatch;
    int socket_cpu_kernel_interrupt;
    int socket_cpu_memoria;
    int socket_escucha;

    decir_hola("CPU");

    //INSTANCIO LOGGER
    t_log* logger;
    //INICIALIZO LOGGER
    logger = start_logger("log_cpu.log", "LOG CPU", LOG_LEVEL_INFO);

    //INSTACION CONFIG
    t_config* config;
    //INICIALIZO config
    config = start_config("./cpu.config");

    //Cargo y compruebo la config
    ip_memoria = config_get_string_value(config, "IP_MEMORIA");
    log_info(logger, "IP leido: %s", ip_memoria);

    puerto_memoria = config_get_string_value(config, "PUERTO_MEMORIA");
    log_info(logger, "PUERTO memoria leido: %s", puerto_memoria);

    puerto_escucha_dispatch = config_get_string_value(config, "PUERTO_ESCUCHA_DISPATCH");
    log_info(logger, "PUERTO dispatch leido: %s", puerto_escucha_dispatch);

    puerto_escucha_interrupt = config_get_string_value(config, "PUERTO_ESCUCHA_INTERRUPT");
    log_info(logger, "PUERTO interrupt leido: %s", puerto_escucha_interrupt);

    //Pruebas con memoria
    //crear conexion
    socket_cpu_memoria = crear_conexion(ip_memoria, puerto_memoria);
    //recibir mensaje
    op_code codop1 = recibir_operacion(socket_cpu_memoria);    
    if (codop1 == MENSAJE) {log_info(logger, "LLego un mensaje");}
    else {log_info(logger, "LLego otra cosa");}
    recibir_mensaje(socket_cpu_memoria, logger);
    //enviar mensaje
    enviar_mensaje("CPU manda mensaje a Memoria", socket_cpu_memoria);
    log_info(logger, "Se envio el primer mensaje a memoria");

    uint32_t PID = 0;
    t_contexto_ejecucion CE;
    CE.PC = 0;
    CE.AX = 0;
    CE.BX = 0;
    CE.CX = 0;
    CE.DX = 0;
    CE.EAX = 0;
    CE.EBX = 0;
    CE.ECX = 0;
    CE.EDX = 0;
    CE.SI = 0;
    CE.DI = 0;
    log_info(logger, "CE contenedor listo, datos: PID=%d, PC=%d, AX=%d, EAX=%d, SI=%d", PID, CE.PC, CE.AX, CE.EAX, CE.SI);

    op_code codopCE = recibir_operacion(socket_cpu_memoria);    
    if (codopCE == CONTEXTO) {log_info(logger, "LLego un contexto de ejecucion");}
    recibir_CE(socket_cpu_memoria, &PID, &CE);
    log_info(logger, "datos nuevos CE contenedor: PID=%d, PC=%d, AX=%d, EAX=%d, SI=%d", PID, CE.PC, CE.AX, CE.EAX, CE.SI);

    // //Pruebas con kernel
    // //iniciar Server de CPU
    // socket_escucha = iniciar_servidor(puerto_escucha_dispatch, logger);

    // //esperar conexion de kernel
    // socket_cpu_kernel_dispatch = esperar_cliente(socket_escucha, logger);
    // //enviar mensaje a kernel
    // enviar_mensaje("CPU manda mensaje a Kernel", socket_cpu_kernel_dispatch);
    // log_info(logger, "Se envio el primer mensaje a kernel");

    // //recibir respuesta de kernel
    // op_code codop2 = recibir_operacion(socket_cpu_kernel_dispatch);
    
    // if (codop2 == MENSAJE) {log_info(logger, "LLego un mensaje");}
    // else {log_info(logger, "LLego otra cosa");}
    // recibir_mensaje(socket_cpu_kernel_dispatch, logger);

    if (socket_cpu_kernel_dispatch) {liberar_conexion(socket_cpu_kernel_dispatch);}
    if (socket_cpu_kernel_interrupt) {liberar_conexion(socket_cpu_kernel_interrupt);}
    if (socket_cpu_memoria) {liberar_conexion(socket_cpu_memoria);}
    if (socket_escucha) {liberar_conexion(socket_escucha);}

    return 0;
}


