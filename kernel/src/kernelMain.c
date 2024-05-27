#include "../include/kernelMain.h"

int main(int argc, char* argv[]) {



    decir_hola("Kernel");
//INICIALIZO LOS LOGS Y CONGIFURACIONES 
    iniciar_Kernel();


// INICIALIZO SERVIDOR KERNEL
    socket_escucha = iniciar_servidor(puerto_escucha, logger);


//CONECTO CON MEMORIA
    socket_memoria_kernel = crear_conexion(ip_memoria, puerto_memoria);
    log_info(logger_debug,"Kernel conectado a MEMORIA");

 //CONECTO CON CPU
    socket_kernel_cpu_dispatch = crear_conexion(ip_cpu, puerto_cpu_dispatch);
    log_info(logger_debug,"Kernel conectado a CPU dispatch");

    socket_kernel_cpu_interrupt = crear_conexion(ip_cpu, puerto_cpu_interrupt);
    log_info(logger_debug,"Kernel conectado a CPU interrupt");

//ESPERO QUE SE CONECTE I/O
    socket_entradasalida_kernel = esperar_cliente(socket_escucha, logger);
    log_info(logger_debug,"Kernel conectado a I/O");


  

      /////////////////////////////////////                AHORA ATENDEMOS LAS CONEXIONES                        //////////////////////////////////////////////////////

    // CREO HILO DE CPU DISPARCH
        pthread_t hilo_CPU_dispatch;
        pthread_create(&hilo_CPU_dispatch,NULL,(void*)atender_conexion_CPU_DISPATCH_KERNEL,NULL);
        pthread_detach(hilo_CPU_dispatch);    
            
    // CREO HILO DE CPU INTERRUPT
        pthread_t hilo_CPU_interrupt;
        pthread_create(&hilo_CPU_interrupt,NULL,(void*)atender_conexion_CPU_INTERRUPT_KERNEL,NULL);
        pthread_detach(hilo_CPU_interrupt); 

    //CREO HILO de MEMORIA
        pthread_t hilo_MEMORIA;
        pthread_create(&hilo_MEMORIA,NULL,(void*)atender_conexion_MEMORIA_KERNELL,NULL);
        pthread_detach(hilo_CPU_interrupt); 
                   
    // CREO HILO ENTRADA-SALIDA
        pthread_t hilo_entradaSalida;
        pthread_create(&hilo_entradaSalida,NULL,(void*)atender_conexion_ENTRADASALIDA_KERNEL,NULL);
        pthread_join(hilo_entradaSalida,NULL);




 




    //Planificacion
    //pthread_create(&hilo_sts, NULL, (void*)pcp_planificar, NULL);


    if (socket_kernel_cpu_dispatch) {liberar_conexion(socket_kernel_cpu_dispatch);}
    if (socket_kernel_cpu_interrupt) {liberar_conexion(socket_kernel_cpu_interrupt);}
    if (socket_memoria_kernel) {liberar_conexion(socket_memoria_kernel);}
    if (socket_entradasalida_kernel) {liberar_conexion(socket_entradasalida_kernel);}
    if (socket_escucha) {liberar_conexion(socket_escucha);}
    return 0;
}
