#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>  // Para usleep
#endif

void limpiar_pantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

double obtener_tiempo_actual() {
    return (double)clock() / CLOCKS_PER_SEC;
}

void pausa_ms(int milisegundos) {
    #ifdef _WIN32
        Sleep(milisegundos);
    #else
        // usleep está obsoleto pero funciona, podemos ignorar la advertencia
        // o usar la versión con declaración explícita
        usleep(milisegundos * 1000);
    #endif
}
