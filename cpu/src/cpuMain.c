#include "../include/cpuMain.h"

int main(int argc, char* argv[]) {

    uint32_t PID = 0;
    t_contexto_ejecucion contexto_interno;
    interrupcion = INT_NO;
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
    // socket_cpu_memoria = crear_conexion(ip_memoria, puerto_memoria);

    // log_info(logger, "CE contenedor listo, datos: PID=%d, PC=%d, AX=%d, EAX=%d, SI=%d", PID, contexto_interno.PC, contexto_interno.AX, contexto_interno.EAX, contexto_interno.SI);

    // op_code codopCE = recibir_operacion(socket_cpu_memoria);    
    // if (codopCE == CONTEXTO) {log_info(logger, "LLego un contexto de ejecucion");}
    // recibir_CE(socket_cpu_memoria, &PID, &contexto_interno);
    // log_info(logger, "datos nuevos CE contenedor: PID=%d, PC=%d, AX=%d, EAX=%d, SI=%d", PID, contexto_interno.PC, contexto_interno.AX, contexto_interno.EAX, contexto_interno.SI);

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
    recibir_proceso(socket_cpu_kernel_dispatch, &PID, &contexto_interno);

    while(true){
        t_instruccion* ins_actual = fetch(PID, contexto_interno.PC, socket_cpu_memoria);
        ejecutar_instruccion(PID, &contexto_interno, ins_actual);
        if (check_interrupt(interrupcion, PID, contexto_interno)) {
            recibir_proceso(socket_cpu_kernel_dispatch, &PID, &contexto_interno);
        };
    }
    // Pruebas
    log_info(logger, "I: PID: %d, PC: %d, EAX: %d", PID, contexto_interno.PC, contexto_interno.EAX);
    t_instruccion* ins1 = malloc(sizeof(t_instruccion));
    ins1->ins = SET;
    ins1->arg1 = "EAX";
    ins1->arg2 = "15";

    ejecutar_instruccion(PID, &contexto_interno, ins1);
    log_info(logger, "II: PID: %d, PC: %d, EAX: %d", PID, contexto_interno.PC, contexto_interno.EAX);
    
    t_instruccion* ins2 = malloc(sizeof(t_instruccion));
    ins2->ins = SET;
    ins2->arg1 = "EBX";
    ins2->arg2 = "5";
    ejecutar_instruccion(PID, &contexto_interno, ins2);
    log_info(logger, "III: PID: %d, PC: %d, EBX: %d", PID, contexto_interno.PC, contexto_interno.EBX);
    
    t_instruccion* ins3 = malloc(sizeof(t_instruccion));
    ins3->ins = SUB;
    ins3->arg1 = "EAX";
    ins3->arg2 = "EBX";
    ejecutar_instruccion(PID, &contexto_interno, ins3);
    log_info(logger, "IV: PID: %d, PC: %d, EAX: %d", PID, contexto_interno.PC, contexto_interno.EAX);
    // Fin pruebas

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

void ejecutar_instruccion(uint32_t PID, t_contexto_ejecucion* contexto_interno, t_instruccion* ins_actual){
    cod_ins codigo = ins_actual->ins;
    int tamanio_d;
    int tamanio_o;
    int valor;

    switch (codigo)
    {
    case SET:
        log_info(logger,"PID: %d - Ejecutando: SET - %s %s", PID, ins_actual->arg1, ins_actual->arg2);
        void* registro = direccion_registro(contexto_interno, ins_actual->arg1);
        int tamanio = tam_registro(ins_actual->arg1);
        valor = atoi(ins_actual->arg2);

        memcpy(registro, &valor, tamanio);
        contexto_interno->PC++;
        break;
    case SUM:
        log_info(logger,"PID: %d - Ejecutando: SUM - %s %s", PID, ins_actual->arg1, ins_actual->arg2);
        tamanio_d = tam_registro(ins_actual->arg1);
        tamanio_o = tam_registro(ins_actual->arg2);
        if (tamanio_d != tamanio_o){
            log_error(logger, "SUM trata de sumar registros de distinto tamaño");
            ins_actual->ins = EXIT; //al tener un error, el proceso sale de CPU
            //falta el break a proposito
        }
        else{   
            if (tamanio_d==8){
            uint8_t* registro_destino = direccion_registro(contexto_interno, ins_actual->arg1);
            uint8_t* registro_origen = direccion_registro(contexto_interno, ins_actual->arg2);
            uint8_t valor8 = *registro_destino + *registro_origen;
            memcpy(registro_destino, &valor8, sizeof(valor8));
            }
            else{
            uint32_t* registro_destino = direccion_registro(contexto_interno, ins_actual->arg1);
            uint32_t* registro_origen = direccion_registro(contexto_interno, ins_actual->arg2);
            uint32_t valor32 = *registro_destino + *registro_origen;
            memcpy(registro_destino, &valor32, sizeof(valor32));
            }
            contexto_interno->PC++;
            break;
        }
    case SUB:
        log_info(logger,"PID: %d - Ejecutando: SUB - %s %s", PID, ins_actual->arg1, ins_actual->arg2);
        tamanio_d = tam_registro(ins_actual->arg1);
        tamanio_o = tam_registro(ins_actual->arg2);
        if (tamanio_d != tamanio_o){
            log_error(logger, "SUB trata de restar registros de distinto tamaño");
            ins_actual->ins = EXIT; //al tener un error, el proceso sale de CPU
            //falta el break a proposito
        }
        else{   
            if (tamanio_d==8){
            uint8_t* registro_destino = direccion_registro(contexto_interno, ins_actual->arg1);
            uint8_t* registro_origen = direccion_registro(contexto_interno, ins_actual->arg2);
            uint8_t valor = *registro_destino - *registro_origen;
            memcpy(registro_destino, &valor, sizeof(valor));
            }
            else{
            uint32_t* registro_destino = direccion_registro(contexto_interno, ins_actual->arg1);
            uint32_t* registro_origen = direccion_registro(contexto_interno, ins_actual->arg2);
            uint32_t valor = *registro_destino - *registro_origen;
            memcpy(registro_destino, &valor, sizeof(valor));
            }
            contexto_interno->PC++;
            break;
        }
        break;
    case JNZ:
        break;
    case IO_GEN_SLEEP:
        break;
    case EXIT:
        break;
    default:
        break;
    }
}

void* direccion_registro(t_contexto_ejecucion* contexto, char* registro){

    if (string_equals_ignore_case(registro, "AX"))  {return &(contexto->AX);}
    else if (string_equals_ignore_case(registro, "BX"))  {return &(contexto->BX);}
    else if (string_equals_ignore_case(registro, "CX"))  {return &(contexto->CX);}
    else if (string_equals_ignore_case(registro, "DX"))  {return &(contexto->DX);}
    else if (string_equals_ignore_case(registro, "EAX"))  {return &(contexto->EAX);}
    else if (string_equals_ignore_case(registro, "EBX"))  {return &(contexto->EBX);}
    else if (string_equals_ignore_case(registro, "ECX"))  {return &(contexto->ECX);}
    else if (string_equals_ignore_case(registro, "EDX"))  {return &(contexto->EDX);}
    else if (string_equals_ignore_case(registro, "SI"))  {return &(contexto->SI);}
    else if (string_equals_ignore_case(registro, "DI"))  {return &(contexto->DI);}
    else {
        log_error(logger, "Error en traduccion de string a registro");
        return NULL;
    }
}

int tam_registro(char* registro){
    if (!string_equals_ignore_case(registro, "AX")
    ||(!string_equals_ignore_case(registro, "BX"))
    ||(!string_equals_ignore_case(registro, "CX"))
    ||(!string_equals_ignore_case(registro, "DX"))
    )   {return 8;}
    else {return 32;}
}

bool check_interrupt(int_code interrupcion, uint32_t PID, t_contexto_ejecucion contexto_interno){
    if (interrupcion != INT_NO)
    {
        enviar_CE(socket_cpu_kernel_dispatch, PID, contexto_interno);
        return true;
    }
    return false;
}

void recibir_proceso(int socket_cpu_kernel_dispatch, uint32_t* PID, t_contexto_ejecucion* contexto_interno){
    recibir_CE(socket_cpu_kernel_dispatch, PID, contexto_interno);
    interrupcion = INT_NO;
}
