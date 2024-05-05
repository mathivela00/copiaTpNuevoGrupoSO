#include "Memoria-CPU.h"

void atender_conexion_CPU_MEMORIA(){

    pthread_t hilo_enviar_a_CPU_memoria;
    pthread_create(&hilo_enviar_a_CPU_memoria,NULL,(void*)enviar_a_CPU,NULL);
    pthread_detach( hilo_enviar_a_CPU_memoria);

    pthread_t hilo_escucha_CPU_memoria;
    pthread_create(&hilo_escucha_CPU_memoria,NULL,(void*)escuchar_a_CPU,NULL);
    pthread_join(hilo_escucha_CPU_memoria,NULL);

}


void escuchar_a_CPU(){


    bool continuarIterando=1;
    t_list* lista;    
        while (continuarIterando) {
            int cod_op = recibir_operacion(fd_CPU);
            switch (cod_op) {
            case HANDSHAKE:
                recibir_mensaje(fd_CPU,logger_memoria);
                break;
            case PAQUETE:
                lista = recibir_paquete(fd_CPU);
                log_info(logger_memoria_db, "Me llegaron los siguientes valores:\n");
                list_logger(lista,logger_memoria_db);
                // list_iterate(lista, (void*) iterator);
                break;
            case -1:
                log_error(logger_memoria_db, "el CPU SE DESCONECTO. Terminando servidor");
                continuarIterando=0;
                break;
            default:
                log_warning(logger_memoria_db,"Operacion desconocida de CPU. No quieras meter la pata");
                break;
            }
        }

}

void enviar_a_CPU(){

    enviar_mensaje("MEMORIA",fd_CPU);
    
    while (1){
        paquete(fd_CPU);
}
}

