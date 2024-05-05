#include "CPU.h"

int main(int argc, char* argv[]) {
    
//INICIALIZO LOS LOGS Y CONGIFURACIONES
    iniciar_CPU();


// INICIALIZO SERVIDOR CPU DISPATCH
    fd_CPU_dispatch=iniciar_servidor(PUERTO_ESCUCHA_DISPATCH,logger_CPU,"CPU (DISIPATCH) SERVIDOR LISTO!!!");

// INICIALIZO SERVIDOR CPU INTERRUPT
    fd_CPU_interrupt=iniciar_servidor(PUERTO_ESCUCHA_INTERRUPT,logger_CPU,"CPU (INTERRUPT) SERVIDOR LISTO!!!");
 


// CONECTO A MEMORIA
    fd_memoria= crear_conexion(IP_MEMORIA,PUERTO_MEMORIA);
    log_warning(logger_CPU_db,"CPU conectado a memoria");



// ESPERO QUE SE CONECTE KERNEL DISPATCH
    log_trace(logger_CPU_db,"Esperando que se concte KERNEL DISPATCH");
    fd_kernel_dispatch=esperar_cliente(fd_CPU_dispatch,logger_CPU,"KERNEL (INTERRUPT)");

// ESPERO QUE SE CONECTE KERNEL INTERRUPT
    log_trace(logger_CPU_db,"Esperando que se concte KERNEL INTERRUPT");
    fd_kernel_interrupt=esperar_cliente(fd_CPU_interrupt,logger_CPU,"KERNEL (INTERRUPT)");


/////////////////////////////////////                AHORA ATENDEMOS LAS CONEXIONES                        //////////////////////////////////////////////////////

/*
// atender mensajes DE KERNEL DISPATCH
    pthread_t hilo_kernel_dispatch;
    pthread_create(&hilo_kernel_dispatch,NULL,(void*)atender_conexion_KERNEL_DISPATCH,NULL);
    pthread_detach(hilo_kernel_dispatch);

// atender mensajes KERNEL INTERRUPT
    pthread_t hilo_kernel_interrupt;
    pthread_create(&hilo_kernel_interrupt,NULL,(void*)atender_conexion_KERNEL_INTERRUPT_CPU,NULL);
    pthread_detach(hilo_kernel_interrupt);
*/

// atender mensajes de MEMORIA 
    pthread_t hilo_memoria;
    pthread_create(&hilo_memoria,NULL,(void*)atender_conexion_MEMORIA_CPU,NULL);
    pthread_join(hilo_memoria,NULL);

    return 0;
}
