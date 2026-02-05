#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

// ============================================================================
// ESTRUCTURAS DE DATOS
// ============================================================================

// Estructura para los datos del ejercicio de reflejos
typedef struct {
    int total_intentos;
    int aciertos;
    double *tiempos;  // Array dinámico de tiempos
    char *teclas_correctas;  // Array dinámico de teclas objetivo
    char *teclas_presionadas;  // Array dinámico de teclas del usuario
} DatosReflejos;

// Estructura para los datos del ejercicio de caza de caracteres
typedef struct {
    int total_rondas;
    int aciertos;
    double *tiempos;  // Array dinámico de tiempos
    char *caracteres_objetivo;  // Array dinámico de caracteres objetivo
    char *caracteres_presionados;  // Array dinámico de caracteres del usuario
} DatosCazaCaracteres;

// Estructura para los datos del ejercicio de cálculo mental
typedef struct {
    int total_operaciones;
    int aciertos;
    int puntuacion;
    double *tiempos;  // Array dinámico de tiempos
} DatosCalculo;

// Estructura para los datos del ejercicio de memoria
typedef struct {
    int total_rondas;
    int aciertos;
    int longitud_maxima;
    int *secuencia_correcta;  // Array dinámico
    int *secuencia_usuario;  // Array dinámico
    int capacidad_secuencia;  // Tamaño del array (máximo 7 por defecto)
} DatosMemoria;

// ============================================================================
// FUNCIONES DE GESTIÓN DE MEMORIA
// ============================================================================

// Reflejos
DatosReflejos* crear_datos_reflejos(int num_intentos);
void liberar_datos_reflejos(DatosReflejos *datos);

// Caza de caracteres
DatosCazaCaracteres* crear_datos_caza(int num_rondas);
void liberar_datos_caza(DatosCazaCaracteres *datos);

// Cálculo mental
DatosCalculo* crear_datos_calculo(int num_operaciones);
void liberar_datos_calculo(DatosCalculo *datos);

// Memoria
DatosMemoria* crear_datos_memoria(int num_rondas, int capacidad_secuencia);
void liberar_datos_memoria(DatosMemoria *datos);

// ============================================================================
// FUNCIONES DE EJERCICIOS (INTERFAZ PÚBLICA)
// ============================================================================

// Ejercicio de reflejos para mano derecha
void ejercicio_reflejos_mano_derecha();
void mostrar_estadisticas_reflejos(DatosReflejos *datos);

// Ejercicio caza de caracteres
void ejercicio_caza_caracteres();
void mostrar_estadisticas_caza(DatosCazaCaracteres *datos);

// Ejercicio cálculo mental
void ejercicio_calculo_mental();
void generar_operacion(int nivel, int *a, int *b, char *operador, int *resultado, int *tiempo_limite);
void mostrar_estadisticas_calculo(DatosCalculo *datos);

// Ejercicio memoria
void ejercicio_memoria_numeros();
void mostrar_estadisticas_memoria(DatosMemoria *datos);

#endif
