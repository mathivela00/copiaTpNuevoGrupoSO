#include "memoria.h"

int main(int argc, char* argv[]) {
    
 //INICIALIZO LOS LOGS Y CONGIFURACIONES

    iniciar_memoria();

// INICIALIZO LA MEMORIA
    fd_memoria=iniciar_servidor(PUERTO_ESCUCHA,logger_memoria,"MEMORIA SERVIDOR LISTA!!!");



// ESPERO QUE SE CONECTE CPU
    log_trace(logger_memoria_db,"Esperando que se concte CPU");
    fd_CPU=esperar_cliente(fd_memoria,logger_memoria,"CPU");


// ESPERO QUE SE CONECTE EL KERNEL
    log_trace(logger_memoria_db,"Esperando que se concte KERNEL");
    fd_kernel=esperar_cliente(fd_memoria,logger_memoria,"KERNEL");


// ESPERO QUE SE CONECTE I/O
    log_trace(logger_memoria_db,"Esperando que se concte I/O");
    fd_entradaSalida=esperar_cliente(fd_memoria,logger_memoria,"I/O");


/////////////////////////////////////                AHORA ATENDEMOS LAS CONEXIONES                        //////////////////////////////////////////////////////


// atender mensajes DE CPU
    pthread_t hilo_CPU;
    pthread_create(&hilo_CPU,NULL,(void*)atender_conexion_CPU_MEMORIA,NULL);
    //pthread_detach(hilo_CPU);
     pthread_join(hilo_CPU,NULL);
/*
// atender mensajes DE KERNEL
    pthread_t hilo_kernel;
    pthread_create(&hilo_kernel,NULL,(void*)atender_conexion_KERNEL_MEMORIA,NULL);
    pthread_detach(hilo_kernel);


// atender mensajes DE ENTRADA/SALIDA
    pthread_t hilo_entradaSalida;
    pthread_create(&hilo_entradaSalida,NULL,(void*)atender_conexion_ENTRADASALIDA_MEMORIA,NULL);
    pthread_join(hilo_entradaSalida,NULL);


*/









    return 0;
}
