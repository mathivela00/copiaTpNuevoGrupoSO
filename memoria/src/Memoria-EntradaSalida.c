#include "Memoria-EntradaSalida.h"

void atender_conexion_ENTRADASALIDA_MEMORIA(){
    bool continuarIterando=1;
    t_list* lista;    
        while (continuarIterando) {
            int cod_op = recibir_operacion(fd_entradaSalida);
            switch (cod_op) {
            case HANDSHAKE:
                recibir_mensaje(fd_entradaSalida,logger_memoria);
                break;
            case PAQUETE:
                lista = recibir_paquete(fd_entradaSalida);
                log_info(logger_memoria_db, "Me llegaron los siguientes valores:\n");
                list_logger(lista,logger_memoria_db);
                // list_iterate(lista, (void*) iterator);
                break;
            case -1:
                log_error(logger_memoria_db, "el MODULO DE ENTRADAS Y SALIDAS SE DESCONECTO. Terminando servidor");
                continuarIterando=0;
                break;
            default:
                log_warning(logger_memoria_db,"Operacion desconocida de ENTRADAS Y SALIDAS. No quieras meter la pata");
                break;
            }
        }


}
