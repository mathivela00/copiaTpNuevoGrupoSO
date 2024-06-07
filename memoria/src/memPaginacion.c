#include "../include/memPaginacion.h"

t_bitarray* bitmap;
t_list* tablaDePaginas;

void inicializarMem(){
    memoria_usuario = malloc(tam_memoria);

    if(memoria_usuario==NULL){
        perror("Fallo al inicializar memoria de usuario");
        exit(EXIT_FAILURE);
    }

    memset(memoria_usuario, 0, tam_memoria); //INCIALIZA TODA LA MEMORIA EN 0

    log_info(logger, "Memoria de usuario inicializada con %d frames de %d bytes cada uno", cant_frames, tam_pagina);

    int tam_bitarray = (cant_frames + 7) / 8; //TAMAÑO EN BYTES redondeando hacia arriba
    char* bitarray_mem = malloc(tam_bitarray);
    if (bitarray_mem == NULL) {
        log_error(logger, "Fallo asignacion memoria al bitarray");
        exit(EXIT_FAILURE);
    }
    memset(bitarray_mem, 0, tam_bitarray);  // Inicializa el bit array a 0 (todos los marcos libres)
    bitmap = bitarray_create_with_mode(bitarray_mem, tam_bitarray, MSB_FIRST);

    tablaDePaginas = list_create();
    log_info(logger, "BITMAP inicializado correctamente");
}

procesoM* crear_proceso(char* path_instrucciones, uint32_t PID){ 
    procesoM* proceso = malloc(sizeof(procesoM));
    proceso->pid = PID;
    t_list* lista_inst = leer_pseudocodigo(path_instrucciones);
    if(lista_inst==NULL){
        perror("Error al crear la lista de instrucciones");
        return 1;
    }else{proceso->instrs = lista_inst;}

    t_list* tabla_paginas = crear_tabla_pag(0); //empieza con tabla de paginas vacia
    proceso->paginas = tabla_paginas;

    añadirTablaALista(tabla_paginas, PID);

    return proceso;
} 

t_list* crear_tabla_pag(uint32_t size){ 
    int nPags = (size + tam_pagina - 1) / tam_pagina;
    t_list* paginas = list_create();
    tabla_pag* p = malloc(sizeof(tabla_pag));
    p->marco = -1; //no inicializado
    p->presencia = false;

    for(int i=0; i<nPags; ++i){
        list_add(paginas, p);
    } 

    return paginas;
}

void añadirTablaALista(t_list* paginas, uint32_t PID){  
    // añade una tabla de pagina a la lista global de todas las tablas con su PID

    tabla_pag_proceso* nueva_tabla_proceso = malloc(sizeof(tabla_pag_proceso)); 
    if (nueva_tabla_proceso == NULL) {
        perror("Error al crear la tabla del proceso");
        return 1;
    }

    nueva_tabla_proceso->pid = PID;
    nueva_tabla_proceso->paginas = paginas;

    log_info(logger, "Creacion de tabla de paginas: PID: %d. Tamaño: %d", PID, list_size(paginas));

    list_add(tablaDePaginas, nueva_tabla_proceso);
}

tabla_pag_proceso* obtener_tabla_pag_proceso(uint32_t PID){
    for (int i = 0; i < list_size(tablaDePaginas); i++) {
        tabla_pag_proceso* tabla = list_get(tablaDePaginas, i);
        if (tabla->pid == PID) {
            return tabla;
        }
    }
    return NULL;
}

void escribir_memoria(int direccion_fisica, const char* valor){

    if (direccion_fisica >= tam_memoria) {
        log_error(logger, "Error: Dirección física %d fuera de los límites de la memoria", direccion_fisica);
        return;
    }

    // Copiar la cadena de caracteres a la memoria
    strcpy((char*)(memoria_usuario + direccion_fisica), valor);
    log_info(logger, "Escribir: Dirección física %d -> Valor %s", direccion_fisica, valor);
}

char* leer_memoria(int direccion_fisica){

    if (direccion_fisica >= tam_memoria) {
        log_error(logger, "Error: Dirección física %d fuera de los límites de la memoria", direccion_fisica);
        return NULL;
    }

    // Leer la cadena de caracteres desde la memoria
    char* valor = (char*)(memoria_usuario + direccion_fisica);
    log_info(logger, "Leer: Dirección física %d -> Valor %s", direccion_fisica, valor);
    return valor;
}