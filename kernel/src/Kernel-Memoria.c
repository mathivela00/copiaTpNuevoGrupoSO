#include "../include/Kernel-Memoria.h"


    void atender_conexion_MEMORIA_KERNELL(){

//RECIBIR MENSAJE DE MEMORIA
    op_code codop = recibir_operacion(socket_memoria_kernel);
    if (codop == MENSAJE) {printf("LLego un mensaje\n");}
    else {printf("LLego otra cosa");}
    recibir_mensaje(socket_memoria_kernel, logger);

//ENVIAR MENSAJE A MEMORIA
    enviar_mensaje("Kernel manda mensaje a memoria", socket_memoria_kernel);
    log_info(logger, "Se envio el primer mensaje a memoria");

    }