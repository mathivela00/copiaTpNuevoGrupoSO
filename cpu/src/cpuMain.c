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

    uint32_t PID = 0;
    t_contexto_ejecucion contexto_interno;
    int_code interrupcion = INT_NO;

    decir_hola("CPU");

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

    contexto_interno.PC = 0;
    contexto_interno.AX = 0;
    contexto_interno.BX = 0;
    contexto_interno.CX = 0;
    contexto_interno.DX = 0;
    contexto_interno.EAX = 0;
    contexto_interno.EBX = 0;
    contexto_interno.ECX = 0;
    contexto_interno.EDX = 0;
    contexto_interno.DI = 0;
    contexto_interno.SI = 0;

    //Pruebas con memoria
    //crear conexion
    socket_cpu_memoria = crear_conexion(ip_memoria, puerto_memoria);

    log_info(logger, "CE contenedor listo, datos: PID=%d, PC=%d, AX=%d, EAX=%d, SI=%d", PID, contexto_interno.PC, contexto_interno.AX, contexto_interno.EAX, contexto_interno.SI);

    op_code codopCE = recibir_operacion(socket_cpu_memoria);    
    if (codopCE == CONTEXTO) {log_info(logger, "LLego un contexto de ejecucion");}
    recibir_CE(socket_cpu_memoria, &PID, &contexto_interno);
    log_info(logger, "datos nuevos CE contenedor: PID=%d, PC=%d, AX=%d, EAX=%d, SI=%d", PID, contexto_interno.PC, contexto_interno.AX, contexto_interno.EAX, contexto_interno.SI);

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

    // recibir_proceso(socket_cpu_kernel_dispatch);
    while(true){
        t_instruccion* ins_actual = fetch(PID, contexto_interno.PC, socket_cpu_memoria);

    }
    

    if (socket_cpu_kernel_dispatch) {liberar_conexion(socket_cpu_kernel_dispatch);}
    if (socket_cpu_kernel_interrupt) {liberar_conexion(socket_cpu_kernel_interrupt);}
    if (socket_cpu_memoria) {liberar_conexion(socket_cpu_memoria);}
    if (socket_escucha) {liberar_conexion(socket_escucha);}

    end_program(logger, config);

    return 0;
}

t_instruccion* fetch(uint32_t PID, uint32_t PC, int socket_cpu_memoria){
    t_paquete* p = crear_paquete(FETCH);
    agregar_a_paquete_uint32(p, PID);
    agregar_a_paquete_uint32(p, PC);
    enviar_paquete(p, socket_cpu_memoria);
    eliminar_paquete(p);

    return recibir_instruccion(socket_cpu_memoria);
}

t_instruccion* recibir_instruccion(int socket_cpu_memoria){
    op_code op = recibir_operacion(socket_cpu_memoria);
    t_instruccion* instr = malloc(sizeof(t_instruccion*));
    if (op != FETCH){
        log_error(logger, "Llego otra cosa en lugar de una instruccion, codigo:%d", op);
        instr->ins = EXIT;
        return instr;
    }

    uint32_t size;
    int desplazamiento = 0;
    void* buffer = recibir_buffer(&size, socket_cpu_memoria);

    instr->ins = leer_de_buffer_cod_ins(buffer, &desplazamiento);
    instr->arg1 = leer_de_buffer_string(buffer, &desplazamiento);
    instr->arg2 = leer_de_buffer_string(buffer, &desplazamiento);
    instr->arg3 = leer_de_buffer_string(buffer, &desplazamiento);
    instr->arg4 = leer_de_buffer_string(buffer, &desplazamiento);
    instr->arg5 = leer_de_buffer_string(buffer, &desplazamiento);

    free(buffer);

    return instr;
}