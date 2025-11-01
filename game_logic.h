#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

// Ejercicio de reflejos para mano derecha
void ejercicio_reflejos_mano_derecha();
void mostrar_estadisticas_reflejos(double tiempos[], int total_intentos, int aciertos);


// Ejercicio caza de carácteres
void ejercicio_caza_caracteres();
void mostrar_estadisticas_caza(double tiempos[], int total_rondas, int aciertos);

// Ejercicio cálculo mental
void ejercicio_calculo_mental();
void generar_operacion(int nivel, int *a, int *b, char *operador, int *resultado, int *tiempo_limite);
void mostrar_estadisticas_calculo(double tiempos[], int total_ops, int aciertos, int puntuacion);

void ejercicio_memoria_numeros();

#endif
