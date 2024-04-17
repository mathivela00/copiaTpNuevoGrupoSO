#include <stdlib.h>
#include <stdio.h>
#include <utils/utils.h>

int main(int argc, char* argv[]) {

    t_log *logger;
	t_config *config;

    // decir_hola("Kernel");
    logger = iniciar_logger("kernel");
    log_info(logger,"Hola soy kernel");

    return 0;
}
