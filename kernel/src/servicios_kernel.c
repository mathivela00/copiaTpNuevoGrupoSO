#include "../include/servicios_kernel.h"

int asignar pid(){

    int valor_pid;
    pthread_mutex_lock(&mutex_pid);
    valor_pid= identificador_PID;
    identificador_PID++;
    pthread_mutex_unlock(&mutex_pid);


}