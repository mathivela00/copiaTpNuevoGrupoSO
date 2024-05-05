#include "EntradaSalida-Kernel.h"



void atender_conexion_KERNEL_ENTRADASALIDA(){


    pthread_t hilo_enviar_a_KERNEL_ENTRADASALIDA;
    pthread_create(&hilo_enviar_a_KERNEL_ENTRADASALIDA,NULL,(void*)enviar_a_KERNEL,NULL);
    pthread_detach( hilo_enviar_a_KERNEL_ENTRADASALIDA);

    
    pthread_t hilo_escucha_KERNEL_ENTRADASALIDA;
    pthread_create(&hilo_escucha_KERNEL_ENTRADASALIDA,NULL,(void*)escuchar_a_KERNEL,NULL);
    pthread_join(hilo_escucha_KERNEL_ENTRADASALIDA,NULL);



}


void enviar_a_KERNEL(){

    enviar_mensaje("ENTRADASALIDA",fd_kernel);
    
    while (1){
        paquete(fd_kernel);
}
}



void escuchar_a_KERNEL(){
    bool continuarIterando=1;
    t_list* lista;    
        while (continuarIterando) {
            int cod_op = recibir_operacion(fd_kernel);
            switch (cod_op) {
            case HANDSHAKE:
                recibir_mensaje(fd_kernel, logger_entradaSalida);
                break;
            case PAQUETE:
                lista = recibir_paquete(fd_kernel);
                log_info(logger_entradaSalida, "Me llegaron los siguientes valores:\n");
                list_logger(lista,logger_entradaSalida_db);
                break;
            case -1:
                log_error(logger_entradaSalida_db, "La MEMORIA SE DESCONECTO. Terminando servidor");
                continuarIterando=0;
                break;
            default:
                log_warning(logger_entradaSalida_db,"Operacion desconocida de MEMORIA. No quieras meter la pata");
                break;
            }
        }


}




