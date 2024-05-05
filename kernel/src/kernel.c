

#include "kernel.h"

int main(int argc, char const *argv[])
{

    //INICIALIZO LOS LOGS Y CONGIFURACIONES
        iniciar_Kernel();



    // INICIALIZO SERVIDOR KERNEL
        fd_kernel=iniciar_servidor(PUERTO_ESCUCHA,logger_kernel,"KERNEL SERVIDOR LISTO!!!");



    // CONECTO A MEMORIA
        fd_memoria= crear_conexion(IP_MEMORIA,PUERTO_MEMORIA);
        log_warning(logger_kernel_db,"KERNEL conectado a memoria");

    // CONECTO A CPU DISPATCH
        fd_CPU_dispatch= crear_conexion(IP_CPU,PUERTO_CPU_DISPATCH);
        log_warning(logger_kernel_db,"KERNEL conectado a CPU DISPATCH");


    // CONECTO A CPU INTERRUPT  
        fd_CPU_interrupt= crear_conexion(IP_CPU,PUERTO_CPU_INTERRUPT);
        log_warning(logger_kernel_db,"KERNEL conectado a CPU INTERRUPT");
        
        


    // ESPERO QUE SE CONECTE I/O
        log_trace(logger_kernel_db,"KERNEL esperando que se concte I/O");
        fd_entradaSalida=esperar_cliente(fd_kernel,logger_kernel_db,"I/O");



    /////////////////////////////////////                AHORA ATENDEMOS LAS CONEXIONES                        //////////////////////////////////////////////////////
/*
    // atender mensajes DE CPU DISPARCH
        pthread_t hilo_CPU_dispatch;
        pthread_create(&hilo_CPU_dispatch,NULL,(void*)atender_conexion_CPU_DISPATCH_KERNEL,NULL);
        pthread_detach(hilo_CPU_dispatch);    
            
    // atender mensajes DE CPU INTERRUPT
        pthread_t hilo_CPU_interrupt;
        pthread_create(&hilo_CPU_interrupt,NULL,(void*)atender_conexion_CPU_INTERRUPT_KERNEL,NULL);
        pthread_detach(hilo_CPU_interrupt);    
*/                    
    // atender mensajes ENTRADA-SALIDA
        pthread_t hilo_entradaSalida;
        pthread_create(&hilo_entradaSalida,NULL,(void*)atender_conexion_ENTRADASALIDA_KERNEL,NULL);
        pthread_join(hilo_entradaSalida,NULL);



        




    return 0;
}




