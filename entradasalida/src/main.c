#include <stdlib.h>
#include <stdio.h>
#include <utils/utils.h>

int main(int argc, char *argv[])
{
    t_log *logger;
    t_config *config;

    logger = iniciar_logger("io");
    log_info(logger, "Hola soy entrada/salida");

    log_destroy(logger);
    return 0;
}
