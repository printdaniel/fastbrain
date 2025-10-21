#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>    // Para nanosleep
    #include <sys/time.h>  // Para gettimeofday - ALTA PRECISIÓN
#endif

void limpiar_pantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Función de alta precisión para Linux/Mac
double obtener_tiempo_actual_alta_precision() {
#ifdef _WIN32
    // Para Windows
    return (double)clock() / CLOCKS_PER_SEC;
#else
    // Para Linux/Mac - Alta precisión (precisión de microsegundos)
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
#endif
}

void pausa_ms(int milisegundos) {
#ifdef _WIN32
    Sleep(milisegundos);
#else
    // Usar nanosleep - más moderno y sin warnings
    struct timespec ts;
    ts.tv_sec = milisegundos / 1000;
    ts.tv_nsec = (milisegundos % 1000) * 1000000L;
    nanosleep(&ts, NULL);
#endif
}
