#include "../include/memoriaMain.h"

t_log* logger;
char* path_inst;
int tam_pagina;
int tam_memoria;
int retardo;

int main(int argc, char* argv[]) {

    //SERVER
    char* puerto_escucha;
    int socket_cpu_memoria;
    int socket_kernel_memoria;
    int socket_entradasalida_memoria;
    int socket_escucha;

    //INICIALIZO LOGGER
    logger = start_logger("log_memoria.log", "LOG MEMORIA", LOG_LEVEL_INFO);

    //INSTACION CONFIG
    t_config* config;
    //INICIALIZO config
    config = start_config("./memoria.config");

    //OBTENER VALORES CONFIG
    puerto_escucha = config_get_string_value(config, "PUERTO_ESCUCHA");
    log_info(logger, "PUERTO leido: %s", puerto_escucha);
    path_inst = config_get_string_value(config, "PATH_INSTRUCCIONES");
    tam_memoria = config_get_int_value(config, "TAM_MEMORIA");
    log_info(logger, "TAMANIO MEMORIA: %d", tam_memoria);
    tam_pagina = config_get_int_value(config, "TAM_PAGINA");
    log_info(logger, "TAMANIO PAGINA: %d", tam_pagina);
    retardo = config_get_int_value(config, "RETARDO_RESPUESTA");
    log_info(logger, "RETARDO RESPUESTA: %d", retardo);

    //iniciar Server de CPU
    socket_escucha = iniciar_servidor(puerto_escucha, logger);

    //esperar conexiones
    socket_cpu_memoria = esperar_cliente(socket_escucha, logger);
    // socket_kernel_memoria = esperar_cliente(socket_escucha, logger);    
    // socket_entradasalida_memoria = esperar_cliente(socket_escucha, logger);
    
    //Pruebas con CPU
    //enviar mensaje a cpu
    // enviar_mensaje("MEMORIA manda mensaje a cpu", socket_cpu_memoria);
    // log_info(logger, "Se envio el primer mensaje a cpu");

    //recibir respuesta de cpu
    // op_code codop1 = recibir_operacion(socket_cpu_memoria);
    
    //if (codop1 == MENSAJE) {log_info(logger, "LLego un mensaje");}
    //else {log_info(logger, "LLego otra cosa");}
    //recibir_mensaje(socket_cpu_memoria, logger);

    uint32_t PID = 1;
    t_contexto_ejecucion CE;
    CE.PC = 2;
    CE.AX = 1;
    CE.BX = 0;
    CE.CX = 0;
    CE.DX = 0;
    CE.EAX = 32;
    CE.EBX = 0;
    CE.ECX = 0;
    CE.EDX = 0;
    CE.SI = 0;
    CE.DI = 0;
    log_info(logger, "CE listo para enviar, datos: PID=%d, PC=%d, AX=%d, EAX=%d, SI=%d", PID, CE.PC, CE.AX, CE.EAX, CE.SI);
    
    enviar_CE(socket_cpu_memoria, PID, CE);
    log_info(logger, "CE enviado con exito");
    
    // Test local obtencion de instrucciones

    char* path = "test_ins.txt";
    t_list* lista_instrucciones = leer_pseudocodigo("test_ins.txt");
    

    // //Pruebas con kernel
    // //enviar mensaje a kernel
    // enviar_mensaje("MEMORIA manda mensaje a Kernel", socket_kernel_memoria);
    // log_info(logger, "Se envio el primer mensaje a kernel");

    // //recibir respuesta de kernel
    // op_code codop2 = recibir_operacion(socket_kernel_memoria);
    
    // if (codop2 == MENSAJE) {log_info(logger, "LLego un mensaje");}
    // else {log_info(logger, "LLego otra cosa");}
    // recibir_mensaje(socket_kernel_memoria, logger);

    // //Pruebas con entradasalida
    // //enviar mensaje a entradasalida
    // enviar_mensaje("MEMORIA manda mensaje a entradasalida", socket_entradasalida_memoria);
    // log_info(logger, "Se envio el primer mensaje a entradasalida");

    // //recibir respuesta de entradasalida
    // op_code codop3 = recibir_operacion(socket_entradasalida_memoria);
    
    // if (codop3 == MENSAJE) {log_info(logger, "LLego un mensaje");}
    // else {log_info(logger, "LLego otra cosa");}
    // recibir_mensaje(socket_entradasalida_memoria, logger);

    if (socket_cpu_memoria) {liberar_conexion(socket_cpu_memoria);}
    if (socket_kernel_memoria) {liberar_conexion(socket_kernel_memoria);}
    if (socket_entradasalida_memoria) {liberar_conexion(socket_entradasalida_memoria);}
    if (socket_escucha) {liberar_conexion(socket_escucha);}

    return 0;
}

t_list* leer_pseudocodigo(char* path){
    FILE* archivo =  fopen(path, "r");
    t_list* lista_instrucciones = list_create();
    t_instruccion* instr;

    if (archivo == NULL) {printf("No se pudo abrir archivo de pseudocodigo");}

    char linea[50];
    memset(linea, 0, 50);
    while (fgets(linea, 50, archivo) != NULL)
    {
        instr = parsear_instruccion(linea);
        if (!instr) 
        {
            return (t_list* ) NULL;
            break;
        }
        list_add(lista_instrucciones, instr);
    }

    fclose(archivo);
    //printf("Cantidad lineas leidas: [%d]", list_size(lista_instrucciones));

    return lista_instrucciones;
}

t_instruccion* parsear_instruccion(char* linea){
    t_instruccion* instruccion = malloc(sizeof(t_instruccion*));
    char* ins;
    char* a1;
    char* a2;
    char* a3;
    char* a4;
    char* a5;

    char** tokens = string_split(linea, " ");

    ins = tokens[0];    
    switch (hash_ins(ins))
    {
    // 5 argumentos
    case IO_FS_WRITE:
    case IO_FS_READ:
        if (string_array_size(tokens)!=6)
        {
            log_error(logger,"Cantidad incorrecta de argumentos en instruccion");
            return (t_instruccion* ) NULL;
            break;
        }
        a1 = tokens[1];
        a2 = tokens[2];
        a3 = tokens[3];
        a4 = tokens[4];
        a5 = tokens[5];

        string_trim(&a1);
        string_trim(&a2);
        string_trim(&a3);
        string_trim(&a4);
        string_trim(&a5);

        instruccion->ins = hash_ins(ins);
        instruccion->arg1 = a1;
        instruccion->arg2 = a2;
        instruccion->arg3 = a3;
        instruccion->arg4 = a4;
        instruccion->arg5 = a5;
        break;

    // 3 argumentos
    case IO_STDIN_READ:
    case IO_STDOUT_WRITE:
    case IO_FS_TRUNCATE:
        if (string_array_size(tokens)!=4)
        {
            log_error(logger,"Cantidad incorrecta de argumentos en instruccion");
            return (t_instruccion* ) NULL;
            break;
        }
        a1 = tokens[1];
        a2 = tokens[2];
        a3 = tokens[3];
        a4 = string_new();
        a5 = string_new();

        string_trim(&a1);
        string_trim(&a2);
        string_trim(&a3);

        instruccion->ins = hash_ins(ins);
        instruccion->arg1 = a1;
        instruccion->arg2 = a2;
        instruccion->arg3 = a3;
        instruccion->arg4 = a4;
        instruccion->arg5 = a5;
        break;

    // 2 argumentos
    case SET: 
    case SUM:
    case SUB:
    case MOV_IN:
    case MOV_OUT:
    case JNZ:
    case IO_GEN_SLEEP:
    case IO_FS_CREATE:
    case IO_FS_DELETE:
        if (string_array_size(tokens)!=3)
        {
            log_error(logger,"Cantidad incorrecta de argumentos en instruccion");
            return (t_instruccion* ) NULL;
            break;
        }
        a1 = tokens[1];
        a2 = tokens[2];
        a3 = string_new();
        a4 = string_new();
        a5 = string_new();

        string_trim(&a1);
        string_trim(&a2);

        instruccion->ins = hash_ins(ins);
        instruccion->arg1 = a1;
        instruccion->arg2 = a2;
        instruccion->arg3 = a3;
        instruccion->arg4 = a4;
        instruccion->arg5 = a5;
        break;    

    // 1 argumento
    case RESIZE:
    case COPY_STRING:
    case WAIT:
    case SIGNAL:
        if (string_array_size(tokens)!=2)
        {
            log_error(logger,"Cantidad incorrecta de argumentos en instruccion");
            return (t_instruccion* ) NULL;
            break;
        }    
        a1 = tokens[1];
        a2 = string_new();
        a3 = string_new();
        a4 = string_new();
        a5 = string_new();
        string_trim(&a1);
        
        instruccion->ins = hash_ins(ins);
        instruccion->arg1 = a1;
        instruccion->arg2 = a2;
        instruccion->arg3 = a3;
        instruccion->arg4 = a4;
        instruccion->arg5 = a5;
        break;
    case EXIT: // 0 argumentos, solo EXIT
        if (string_array_size(tokens)!=1)
        {
            log_error(logger,"Cantidad incorrecta de argumentos en instruccion");
            return (t_instruccion* ) NULL;
            break;
        }
        a1 = string_new();
        a2 = string_new();
        a3 = string_new();
        a4 = string_new();
        a5 = string_new();

        instruccion->ins = hash_ins(ins);
        instruccion->arg1 = a1;
        instruccion->arg2 = a2;
        instruccion->arg3 = a3;
        instruccion->arg4 = a4;
        instruccion->arg5 = a5;
        break;   
    default:
        log_error(logger, "Instruccion no reconocida");
        return (t_instruccion* ) NULL;
        break;
    }
    return instruccion;
}

cod_ins hash_ins(char* ins){
    if (string_equals_ignore_case(ins, "SET")){return SET;}
    else if (string_equals_ignore_case(ins, "SUM")){return SUM;}
    else if (string_equals_ignore_case(ins, "SUB")){return SUB;}
    else if (string_equals_ignore_case(ins, "MOV_IN")){return MOV_IN;}
    else if (string_equals_ignore_case(ins, "MOV_OUT")){return MOV_OUT;}
    else if (string_equals_ignore_case(ins, "RESIZE")){return RESIZE;}
    else if (string_equals_ignore_case(ins, "JNZ")){return JNZ;}
    else if (string_equals_ignore_case(ins, "COPY_STRING")){return COPY_STRING;}
    else if (string_equals_ignore_case(ins, "IO_GEN_SLEEP")){return IO_GEN_SLEEP;}
    else if (string_equals_ignore_case(ins, "IO_STDIN_READ")){return IO_STDIN_READ;}
    else if (string_equals_ignore_case(ins, "IO_STDOUT_WRITE")){return IO_STDOUT_WRITE;}
    else if (string_equals_ignore_case(ins, "IO_FS_CREATE")){return IO_FS_CREATE;}
    else if (string_equals_ignore_case(ins, "IO_FS_DELETE")){return IO_FS_DELETE;}
    else if (string_equals_ignore_case(ins, "IO_FS_TRUNCATE")){return IO_FS_TRUNCATE;}
    else if (string_equals_ignore_case(ins, "IO_FS_WRITE")){return IO_FS_WRITE;}
    else if (string_equals_ignore_case(ins, "IO_FS_READ")){return IO_FS_READ;}
    else if (string_equals_ignore_case(ins, "WAIT")){return WAIT;}
    else if (string_equals_ignore_case(ins, "SIGNAL")){return SIGNAL;}
    else if (string_equals_ignore_case(ins, "EXIT")){return EXIT;}
    else return -1;
}