#include "../include/atender_operacion.h"

void atender_instruccion_validada(char* leido)
{

    char** array_de_comando= string_split (leido, " ");

    if(strcmp(array_de_comando[0],"EJECUTAR_SCRIPT")==0){
        

    }else if (strcmp(array_de_comando[0],"INICIAR_PROCESO")==0){
        
        
    }else if (strcmp(array_de_comando[0],"FINALIZAR_PROCESO")==0){
        
        
    }else if (strcmp(array_de_comando[0],"DETENER_PLANIFICACION")==0){
       
        
    }else if (strcmp(array_de_comando[0],"INICIAR_PLANIFICACION")==0){
        
        
    }else if (strcmp(array_de_comando[0],"MULTIPROGRAMACION")==0){
        
        
    }else if (strcmp(array_de_comando[0],"PROCESO_ESTADO")==0){
        
        
    }


}
