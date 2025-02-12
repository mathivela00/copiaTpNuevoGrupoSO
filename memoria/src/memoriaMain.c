#include "../include/memoriaMain.h"


int main(int argc, char* argv[]) {
    

    iniciar_memoria();


    //                  LAS CONFIGURACIONES LOS INICIOS DE LOGGER LOS PASE A LA CARPETA INICIO KERNEL
    //                  LAS DECLARACIONES DE LAS VARIABLES LAS PASE A LAS CARPETAS.H
    ///                 LA CARPETA EXTERN_GLOBALS.C ES PARA COMPARTIR LAS VARIABLES QUE NECESITAS QUE SE VEAN DE TODAS LAS DEMAS CARPETAS DEL MODULO (AGREGAR EXTERN ANTES)
    //                  AGREGAR EXTERN ANTES ES PARA QUE EL COMPILADOR NO TOME COMO QUE ESTAR DECLARANDO LA VARIABLE DOS VECES   


// INICIALIZO  SERVIDOR DE MEMORIA
    socket_escucha=iniciar_servidor(puerto_escucha,logger_debug);


// ESPERO QUE SE CONECTE CPU
    log_trace(logger_debug,"Esperando que se conecte CPU");
    socket_cpu_memoria_dispatch=esperar_cliente(socket_escucha,logger_debug);
    socket_cpu_memoria_interrupt=esperar_cliente(socket_escucha,logger_debug);

// ESPERO QUE SE CONECTE EL KERNEL
    log_trace(logger_debug,"Esperando que se concte KERNEL");
    socket_kernel_memoria=esperar_cliente(socket_escucha,logger_debug);

// CREO HILO ENTRADA-SALIDA Y ADENTRO DEL HILO SOPORTO MULTIPLES CONEXIONES
        pthread_t hilo_entradaSalida_memoria;
        pthread_create(&hilo_entradaSalida_memoria,NULL,(void*)atender_conexion_ENTRADASALIDA_MEMORIA,NULL);
        pthread_detach(hilo_entradaSalida_memoria);

// CREO HILO KERNEL 
        pthread_t hilo_kernel_memoria;
        pthread_create(&hilo_kernel_memoria,NULL,(void*)atender_conexion_KERNEL_MEMORIA,NULL);
        pthread_detach(hilo_kernel_memoria);
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

     //Pruebas con CPU
    //enviar mensaje a cpu
    // enviar_mensaje("MEMORIA manda mensaje a cpu", socket_cpu_memoria);
    // log_info(logger, "Se envio el primer mensaje a cpu");

    //recibir respuesta de cpu
    // op_code codop1 = recibir_operacion(socket_cpu_memoria);
    
    //if (codop1 == MENSAJE) {log_info(logger, "LLego un mensaje");}
    //else {log_info(logger, "LLego otra cosa");}
    //recibir_mensaje(socket_cpu_memoria, logger);

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
    
    // Test local obtencion de instrucciones

    char* path_parcial = "test_ins.txt"; //viene de kernel
    char* path = path_completo(path_base, path_parcial);
    // log_info(logger, "path de archivo: %s", path);
    
    t_list* lista_instrucciones = leer_pseudocodigo(path);

    
    // // Pruebas creacion de lista de instrucciones
    // t_instruccion* ins0 = get_ins(lista_instrucciones, 0);
    // t_instruccion* ins2 = get_ins(lista_instrucciones, 2);
    // t_instruccion* ins4 = get_ins(lista_instrucciones, 4);
    // t_instruccion* ins5 = get_ins(lista_instrucciones, 5);
    // log_info(logger, "codigo instruccion 0: %d", ins0->ins);
    // log_info(logger, "codigo instruccion 2: %d", ins2->ins);
    // log_info(logger, "codigo instruccion 4: %d", ins4->ins);
    // log_info(logger, "codigo instruccion 5: %d", ins5->ins);

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

    if (socket_cpu_memoria_dispatch) {liberar_conexion(socket_cpu_memoria_dispatch);}
    if (socket_cpu_memoria_interrupt) {liberar_conexion(socket_cpu_memoria_interrupt);}
    if (socket_kernel_memoria) {liberar_conexion(socket_kernel_memoria);}
    if (socket_entradasalida_memoria) {liberar_conexion(socket_entradasalida_memoria);}
    if (socket_escucha) {liberar_conexion(socket_escucha);}

    return 0;
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
    // log_info(logger, "Archivo pseudocodigo leido, cantidad lineas leidas: [%d]", list_size(lista_instrucciones));

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

char* path_completo(char* path_base, char* path_parcial){
    char* path = string_new();
    string_append(&path, path_base);
    string_append(&path, path_parcial);

    return path;
}

t_instruccion* get_ins(t_list* lista_instrucciones, uint32_t PC){
    t_instruccion* instruccion = malloc(sizeof(t_instruccion*));
    instruccion =  list_get(lista_instrucciones, PC);
    return instruccion;
}

void conexion_con_cpu(int socket_cpu_memoria, t_list* lista_instrucciones){
    op_code codigo;

    while(true){
        codigo = recibir_operacion(socket_cpu_memoria);
        switch (codigo)
        {
        case FETCH:
            uint32_t PID; //por ahora no hace nada, sera relevante cuando lleguen varios procesos por kernel 
            uint32_t PC;
            recibir_fetch(socket_cpu_memoria, &PID, &PC);
            log_info(logger, "CPU solicita instruccion, PID: %d, PC: %d", PID, PC);

            t_instruccion* sig_ins = get_ins(lista_instrucciones, PC);
            usleep(retardo);
            enviar_instruccion(socket_cpu_memoria, sig_ins);
            log_info(logger, "instruccion enviada");
            break;
        
        default:
            break;
        }
    }
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
