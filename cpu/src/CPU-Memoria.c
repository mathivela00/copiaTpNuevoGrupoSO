#include "CPU-Memoria.h"

void atender_conexion_MEMORIA_CPU(){


    pthread_t hilo_enviar_a_CPU_memoria_CPU;
    pthread_create(&hilo_enviar_a_CPU_memoria_CPU,NULL,(void*)enviar_a_MEMORIA,NULL);
    pthread_detach( hilo_enviar_a_CPU_memoria_CPU);

    
    pthread_t hilo_escucha_memoria_CPU;
    pthread_create(&hilo_escucha_memoria_CPU,NULL,(void*)escuchar_a_MEMORIA,NULL);
    pthread_join(hilo_escucha_memoria_CPU,NULL);



}


void enviar_a_MEMORIA(){

    enviar_mensaje("CPU",fd_memoria);
    
    while (1){
        paquete(fd_memoria);
}
}




void escuchar_a_MEMORIA(){
    bool continuarIterando=1;
    t_list* lista;    
        while (continuarIterando) {
            int cod_op = recibir_operacion(fd_memoria);
            switch (cod_op) {
            case HANDSHAKE:
                recibir_mensaje(fd_memoria, logger_CPU);
                break;
            case PAQUETE:
                lista = recibir_paquete(fd_memoria);
                log_info(logger_CPU_db, "Me llegaron los siguientes valores:\n");
                list_logger(lista,logger_CPU_db);
                break;
            case -1:
                log_error(logger_CPU_db, "La MEMORIA SE DESCONECTO. Terminando servidor");
                continuarIterando=0;
                break;
            default:
                log_warning(logger_CPU_db,"Operacion desconocida de MEMORIA. No quieras meter la pata");
                break;
            }
        }


}

