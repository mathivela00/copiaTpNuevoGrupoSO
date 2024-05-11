#include "CPU-CicloInstruccion.h"


// * * * M O D U L O   D E   C O N T R O L * * * //

// FETCH
/*
Recibe PC lo guarda en cache (PC),
teniendo la direccion fisica, busca  
la instruccion en modulo memoria y se guarda en cache (IR)
Tamaño de IR : respu: mismo q PC (4 Bytes)
*/

void fetch(PCB) {

    PC = PCB.PC;
    enviar_mensaje(PC, socketmemoria);
    IR = recibir_paquete(socketcpu);

}

// DECODE
/*
Parte 1:
Decodificar codigo de operacion, 
es decir usar el mmu para buscar en ram  */

void decode(IR) {

    COP = strchr(IR, primera_palabra);
    datos = strchr(IR, resto_de_palabras);

}

/* Parte 2:
Decodificar las direcciones de los datos, 
es decir usar el mmu para buscar en ram 

COP: cod operacion
[ COP | DATO o DATA ] = IR
8 bits    24 bits
*/ */

// * * * M O D U L O   A L U * * * //

//EXECUTE
/*
Utilizando el COP cargado en la IR, 
genera las microoperaciones para ejecutar la Instruccion

Se define la logica de cada tipo operacion

Ejemplo de instuccion set:
Dependiendo la instruccion, la direccion del dato cargado en el IR
se pasa al MAR para que lo busque en memoria, una vez leido el dato
se pasa al MDR (contenido del puntero)
*/

... excecute(COP, datos) {

    switch (COP)
    {
    case COP == 'SET':
        set(strchr(datos, primera_palabra), strchr(datos, segunda_palabra));
        break;

    case COP == 'SUM':
        sum(strchr(datos, primera_palabra), strchr(datos, segunda_palabra));
        break;

    case COP == 'SUB':
        sub(strchr(datos, primera_palabra), strchr(datos, segunda_palabra));
        break;

    case COP == 'JNZ':
        jnz(strchr(datos, primera_palabra), strchr(datos, segunda_palabra));
        break;

    case COP == 'IO_GEN_SLEEP':
        io_gen_sleep(strchr(datos, primera_palabra), strchr(datos, segunda_palabra));
        break;    
    
    default:
        break;
    }

}
