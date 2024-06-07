#ifndef TP_MEMORIA_PAGINACION_H_
#define TP_MEMORIA_PAGINACION_H_

#include <commons/bitarray.h>
#include <readline/readline.h>
#include "../../utils/include/utils.h"
#include "../../utils/include/conexiones.h"
#include "../include/memoriaMain.h"

typedef struct{
    int pid;
    t_list* instrs;
    t_list* paginas;
}procesoM;

typedef struct{
    int marco;
    bool presencia;
}tabla_pag; //tabla de paginas en si

typedef struct {
    int pid;                  
    t_list* paginas;          // lista de tablas_pag
}tabla_pag_proceso; //tabla de paginas de cada proceso

extern t_bitarray* bitmap;
extern void* memoria_usuario; 
extern t_list* tablaDePaginas;

void inicializarMem();

procesoM* crear_proceso(char* path_instrucciones, uint32_t PID);
void añadirTablaALista(t_list* paginas, uint32_t PID);
t_list* crear_tabla_pag(uint32_t size);
void escribir_memoria(int direccion_fisica, const char* valor);
char* leer_memoria(int direccion_fisica);

#endif //TP_MEMORIA_PAGINACION_H_
