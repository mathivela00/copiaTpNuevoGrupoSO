#include "../include/memoriaMain.h"

t_log* logger;
char* puerto_escucha;
char* path_base;
int tam_pagina;
int tam_memoria;
int retardo;
int cant_frames;
void* memoria_usuario; 
t_config* config;

int main(int argc, char* argv[]) {

    //SERVER
    int socket_cpu_memoria;
    int socket_kernel_memoria;
    int socket_entradasalida_memoria;
    int socket_escucha;

    //INICIALIZO LOGGER
    logger = start_logger("log_memoria.log", "LOG MEMORIA", LOG_LEVEL_INFO);

    //INICIALIZO CONFIG Y OBTENGO DATOS
    cargarConfig();

    // uint32_t PID = 1;
    // t_contexto_ejecucion CE;
    // CE.PC = 2;
    // CE.AX = 1;
    // CE.BX = 0;
    // CE.CX = 0;
    // CE.DX = 0;
    // CE.EAX = 32;
    // CE.EBX = 0;
    // CE.ECX = 0;
    // CE.EDX = 0;
    // CE.SI = 0;
    // CE.DI = 0;
    // log_info(logger, "CE listo para enviar, datos: PID=%d, PC=%d, AX=%d, EAX=%d, SI=%d", PID, CE.PC, CE.AX, CE.EAX, CE.SI);
    
    // enviar_CE(socket_cpu_memoria, PID, CE);
    // log_info(logger, "CE enviado con exito");
    
    // log_info(logger, "path de archivo: %s", path);
    
    //iniciar Server de CPU
    //socket_escucha = iniciar_servidor(puerto_escucha, logger);

    //socket_cpu_memoria = esperar_cliente(socket_escucha, logger);

    //conexion_con_cpu(socket_cpu_memoria);
    
    // // pruebas memoria
    inicializarMem();
    
    escribir_memoria(100, "Hola Mundo");

    char* leido = leer_memoria(100);

    if (socket_cpu_memoria) {liberar_conexion(socket_cpu_memoria);}
    if (socket_kernel_memoria) {liberar_conexion(socket_kernel_memoria);}
    if (socket_entradasalida_memoria) {liberar_conexion(socket_entradasalida_memoria);}
    if (socket_escucha) {liberar_conexion(socket_escucha);}

    return 0;
}

void cargarConfig(){
    //INICIALIZO config
    config = start_config("./memoria.config");

    if(config==NULL){
        perror("Fallo al crear el archivo config");
        exit(EXIT_FAILURE);
    }

    //OBTENER VALORES CONFIG
    puerto_escucha = config_get_string_value(config, "PUERTO_ESCUCHA");
    log_info(logger, "PUERTO leido: %s", puerto_escucha);

    path_base = config_get_string_value(config, "PATH_INSTRUCCIONES");
    log_info(logger, "PATH: %s", path_base);

    tam_memoria = config_get_int_value(config, "TAM_MEMORIA");
    log_info(logger, "TAMANIO MEMORIA: %d", tam_memoria);

    tam_pagina = config_get_int_value(config, "TAM_PAGINA");
    log_info(logger, "TAMANIO PAGINA: %d", tam_pagina);

    retardo = config_get_int_value(config, "RETARDO_RESPUESTA");
    log_info(logger, "RETARDO RESPUESTA: %d", retardo);

    cant_frames = tam_memoria/tam_pagina;
}

t_list* leer_pseudocodigo(char* path){
    FILE* archivo =  fopen(path, "r");
    t_list* lista_instrucciones = list_create();
    t_instruccion* instr;

    if (archivo == NULL) {
        log_error(logger, "No se pudo abrir archivo de pseudocodigo");
        return (t_list*) NULL;    
    }

    char linea[50];
    memset(linea, 0, 50);
    while (fgets(linea, 50, archivo) != NULL)
    {
        instr = parsear_instruccion(linea);
        // log_info(logger, "Ins: %d", instr->ins);
        if (!instr) 
        {
            log_error(logger, "El archivo de pseudocodigo tiene errores/instrucciones invalidas");
            return (t_list* ) NULL;
            break;
        }
        list_add(lista_instrucciones, instr);
    }

    fclose(archivo);
    log_info(logger, "Archivo pseudocodigo leido, cantidad lineas leidas: [%d]", list_size(lista_instrucciones));

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

// char* path_completo(char* path_base, char* path_parcial){
    //char* path = string_new();
    //string_append(&path, path_base);
    //string_append(&path, path_parcial);

    //return path;
//}

t_instruccion* get_ins(t_list* lista_instrucciones, uint32_t PC){
    t_instruccion* instruccion = malloc(sizeof(t_instruccion*));
    instruccion =  list_get(lista_instrucciones, PC);
    return instruccion;
}

void conexion_con_cpu(int socket_cpu_memoria){
    op_code codigo;

    while(true){
        codigo = recibir_operacion(socket_cpu_memoria);
        switch (codigo)
        {
        case FETCH:
            fetch(socket_cpu_memoria);
            break;
        
        default:
            break;
        }
    }
}

void fetch(int socket_cpu_memoria){
    uint32_t PID; //por ahora no hace nada, sera relevante cuando lleguen varios procesos por kernel 
    uint32_t PC;
    recibir_fetch(socket_cpu_memoria, PID, PC);
    log_info(logger, "CPU solicita instruccion, PID: %d, PC: %d", PID, PC);

    t_list* lista_instrucciones = leer_pseudocodigo(path_base);
    t_instruccion* sig_ins = get_ins(lista_instrucciones, PC);
    usleep(retardo);
    enviar_instruccion(socket_cpu_memoria, sig_ins);
    log_info(logger, "instruccion enviada");
}

void recibir_fetch(int socket_cpu_memoria, uint32_t* PID, uint32_t* PC){
    uint32_t size;
    int desplazamiento = 0;
    void* buffer = recibir_buffer(&size, socket_cpu_memoria);

    *PID = leer_de_buffer_uint32(buffer, &desplazamiento);
    *PC = leer_de_buffer_uint32(buffer, &desplazamiento);
}

void enviar_instruccion(int socket_cpu_memoria, t_instruccion* instruccion){
    t_paquete* paquete = crear_paquete(FETCH);
    //log_info(logger, "Paquete creado");
    agregar_a_paquete_cod_ins(paquete, instruccion->ins);
    agregar_a_paquete_string(paquete, strlen(instruccion->arg1) + 1, instruccion->arg1);
    agregar_a_paquete_string(paquete, strlen(instruccion->arg2) + 1, instruccion->arg2);
    agregar_a_paquete_string(paquete, strlen(instruccion->arg3) + 1, instruccion->arg3);
    agregar_a_paquete_string(paquete, strlen(instruccion->arg4) + 1, instruccion->arg4);
    agregar_a_paquete_string(paquete, strlen(instruccion->arg5) + 1, instruccion->arg5);

    enviar_paquete(paquete, socket);
    //log_info(logger, "Paquete enviado");
    eliminar_paquete(paquete);
}