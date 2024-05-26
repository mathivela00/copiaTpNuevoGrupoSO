#include "../include/conexionesCPU.h"

// int startServer(char* puerto_escucha){

//     //INSTANCIO LOGGER
//     t_log* logger;
//     //INICIALIZO LOGGER
//     logger = start_logger("logCpuServer.log", "ServidorCPU", LOG_LEVEL_DEBUG);

//     log_info(logger, "ENTRE PARA INICIAR SERVIDOR.");

//     int server_fd = iniciar_servidor(puerto_escucha, logger);

//     log_info(logger, "Servidor listo para recibir al cliente, server fd: %d", server_fd);
//     int cliente_fd = esperar_cliente(server_fd, logger);
//     log_info(logger, "cliente fd: %d", cliente_fd);

//     t_list* lista;
//     while (1) {
//         int cod_op = recibir_operacion(cliente_fd);
//         switch (cod_op) {
//             case MENSAJE:
//                 recibir_mensaje(cliente_fd, logger);
//                 break;
//             case PAQUETE:
//                 lista = recibir_paquete(cliente_fd);
//                 log_info(logger, "Me llegaron los siguientes valores:\n");
//                 list_iterate(lista, (void*) iterator);
//                 break;
//             case -1:
//                 log_error(logger, "el cliente se desconecto. Terminando servidor");
//                 return EXIT_FAILURE;
//             default:
//                 log_warning(logger,"Operacion desconocida. No quieras meter la pata");
//                 break;
//         }
//     }
//     return EXIT_SUCCESS;
// }


