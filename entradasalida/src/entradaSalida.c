#include "entradaSalida.h"

int main(int argc, char* argv[]) {

// INICIALIZO LOS LOGS Y CONGIFURACIONES
    iniciar_entradaSalida();

// CONECTO A MEMORIA
    fd_memoria= crear_conexion(IP_MEMORIA,PUERTO_MEMORIA);
    log_warning(logger_entradaSalida_db,"Conectado a memoria");

// CONECTO A KERNEL
    fd_kernel= crear_conexion(IP_KERNEL,PUERTO_KERNEL);
    log_warning(logger_entradaSalida_db,"Conectado a kernel");


    /////////////////////////////////////                AHORA ATENDEMOS LAS CONEXIONES                        //////////////////////////////////////////////////////
    /*
    // atender mensajes MEMORIA
        pthread_t hilo_MEMORIA;
        pthread_create(&hilo_MEMORIA,NULL,(void*)atender_conexion_MEMORIA_ENTRADASALIDA,NULL);
        pthread_detach(hilo_MEMORIA);    
    */


    // atender mensajes DE KERNEL
        pthread_t hilo_KERNEL;
        pthread_create(&hilo_KERNEL,NULL,(void*)atender_conexion_KERNEL_ENTRADASALIDA,NULL);
        pthread_join(hilo_KERNEL,NULL);    
            






    return 0;
}
