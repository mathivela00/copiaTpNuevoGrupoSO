#include "CPU-Kernel-Interrupt.h"



void atender_conexion_KERNEL_INTERRUPT_CPU(){
/*

    pthread_t hilo_enviar_a_KERNEL_INTERRUPT_CPU;
    pthread_create(&hilo_enviar_a_KERNEL_INTERRUPT_CPU,NULL,(void*)enviar_a_KERNEL_INTERRUPT,NULL);
    pthread_detach(hilo_enviar_a_KERNEL_INTERRUPT_CPU);

    
    pthread_t hilo_escucha_KERNEL_INTERRUPT_CPU;
    pthread_create(&hilo_escucha_KERNEL_INTERRUPT_CPU,NULL,(void*)escuchar_a_KERNEL,NULL);
    pthread_join(hilo_escucha_KERNEL_INTERRUPT_CPU,NULL);
*/


}

/*
void enviar_a_KERNEL_INTERRUPT(){

    enviar_mensaje("MENSAJE",fd_kernel_interrupt);
    
    while (1){
        paquete(fd_kernel_interrupt);
}
}




void escuchar_a_KERNEL_INTERRUPT(){
    bool continuarIterando=1;
    t_list* lista;    
        while (continuarIterando) {
            int cod_op = recibir_operacion(fd_kernel_interrupt);
            switch (cod_op) {
            case HANDSHAKE:
                recibir_mensaje(fd_kernel_interrupt,logger_CPU);
                break;
            case PAQUETE:
                lista = recibir_paquete(fd_kernel_interrupt);
                log_info(logger_CPU_db, "Me llegaron los siguientes valores:\n");
                list_logger(lista,logger_CPU_db);
                // list_iterate(lista, (void*) iterator);
                break;
            case -1:
                log_error(logger_CPU_db, "el KERNEL INTERRUPT SE DESCONECTO. Terminando servidor");
                continuarIterando=0;
                break;
            default:
                log_warning(logger_CPU_db,"Operacion desconocida de KERNEL- INTERRUPT. No quieras meter la pata");
                break;
            }
        }


}


*/