#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include "game_logic.h"
#include "utils.h"

// Constantes
const char TECLAS_MANO_DERECHA[] = "yuiophjklñnm,.-";
const int NUM_TECLAS = 15;

// ============================================================================
// FUNCIONES DE GESTIÓN DE MEMORIA - REFLEJOS
// ============================================================================

DatosReflejos* crear_datos_reflejos(int num_intentos) {
    if (num_intentos <= 0 || num_intentos > 100) {
        fprintf(stderr, "Error: num_intentos debe estar entre 1 y 100\n");
        return NULL;
    }

    DatosReflejos *datos = (DatosReflejos*)malloc(sizeof(DatosReflejos));
    if (datos == NULL) {
        fprintf(stderr, "Error: No se pudo reservar memoria para DatosReflejos\n");
        return NULL;
    }

    datos->total_intentos = num_intentos;
    datos->aciertos = 0;

    datos->tiempos = (double*)malloc(num_intentos * sizeof(double));
    if (datos->tiempos == NULL) {
        free(datos);
        return NULL;
    }

    datos->teclas_correctas = (char*)malloc(num_intentos * sizeof(char));
    if (datos->teclas_correctas == NULL) {
        free(datos->tiempos);
        free(datos);
        return NULL;
    }

    datos->teclas_presionadas = (char*)malloc(num_intentos * sizeof(char));
    if (datos->teclas_presionadas == NULL) {
        free(datos->teclas_correctas);
        free(datos->tiempos);
        free(datos);
        return NULL;
    }

    for (int i = 0; i < num_intentos; i++) {
        datos->tiempos[i] = -1.0;
        datos->teclas_correctas[i] = '\0';
        datos->teclas_presionadas[i] = '\0';
    }

    return datos;
}

void liberar_datos_reflejos(DatosReflejos *datos) {
    if (datos == NULL) return;

    if (datos->teclas_presionadas != NULL) free(datos->teclas_presionadas);
    if (datos->teclas_correctas != NULL) free(datos->teclas_correctas);
    if (datos->tiempos != NULL) free(datos->tiempos);
    free(datos);
}

// ============================================================================
// FUNCIONES DE GESTIÓN DE MEMORIA - CAZA DE CARACTERES
// ============================================================================

DatosCazaCaracteres* crear_datos_caza(int num_rondas) {
    if (num_rondas <= 0 || num_rondas > 100) {
        fprintf(stderr, "Error: num_rondas debe estar entre 1 y 100\n");
        return NULL;
    }

    DatosCazaCaracteres *datos = (DatosCazaCaracteres*)malloc(sizeof(DatosCazaCaracteres));
    if (datos == NULL) {
        fprintf(stderr, "Error: No se pudo reservar memoria para DatosCazaCaracteres\n");
        return NULL;
    }

    datos->total_rondas = num_rondas;
    datos->aciertos = 0;

    datos->tiempos = (double*)malloc(num_rondas * sizeof(double));
    if (datos->tiempos == NULL) {
        free(datos);
        return NULL;
    }

    datos->caracteres_objetivo = (char*)malloc(num_rondas * sizeof(char));
    if (datos->caracteres_objetivo == NULL) {
        free(datos->tiempos);
        free(datos);
        return NULL;
    }

    datos->caracteres_presionados = (char*)malloc(num_rondas * sizeof(char));
    if (datos->caracteres_presionados == NULL) {
        free(datos->caracteres_objetivo);
        free(datos->tiempos);
        free(datos);
        return NULL;
    }

    for (int i = 0; i < num_rondas; i++) {
        datos->tiempos[i] = -1.0;
        datos->caracteres_objetivo[i] = '\0';
        datos->caracteres_presionados[i] = '\0';
    }

    return datos;
}

void liberar_datos_caza(DatosCazaCaracteres *datos) {
    if (datos == NULL) return;

    if (datos->caracteres_presionados != NULL) free(datos->caracteres_presionados);
    if (datos->caracteres_objetivo != NULL) free(datos->caracteres_objetivo);
    if (datos->tiempos != NULL) free(datos->tiempos);
    free(datos);
}

// ============================================================================
// FUNCIONES DE GESTIÓN DE MEMORIA - CÁLCULO MENTAL
// ============================================================================

DatosCalculo* crear_datos_calculo(int num_operaciones) {
    if (num_operaciones <= 0 || num_operaciones > 100) {
        fprintf(stderr, "Error: num_operaciones debe estar entre 1 y 100\n");
        return NULL;
    }

    DatosCalculo *datos = (DatosCalculo*)malloc(sizeof(DatosCalculo));
    if (datos == NULL) {
        fprintf(stderr, "Error: No se pudo reservar memoria para DatosCalculo\n");
        return NULL;
    }

    datos->total_operaciones = num_operaciones;
    datos->aciertos = 0;
    datos->puntuacion = 0;

    datos->tiempos = (double*)malloc(num_operaciones * sizeof(double));
    if (datos->tiempos == NULL) {
        free(datos);
        return NULL;
    }

    for (int i = 0; i < num_operaciones; i++) {
        datos->tiempos[i] = -1.0;
    }

    return datos;
}

void liberar_datos_calculo(DatosCalculo *datos) {
    if (datos == NULL) return;

    if (datos->tiempos != NULL) free(datos->tiempos);
    free(datos);
}

// ============================================================================
// FUNCIONES DE GESTIÓN DE MEMORIA - MEMORIA DE NÚMEROS
// ============================================================================

DatosMemoria* crear_datos_memoria(int num_rondas, int capacidad_secuencia) {
    if (num_rondas <= 0 || num_rondas > 100) {
        fprintf(stderr, "Error: num_rondas debe estar entre 1 y 100\n");
        return NULL;
    }

    if (capacidad_secuencia <= 0 || capacidad_secuencia > 20) {
        fprintf(stderr, "Error: capacidad_secuencia debe estar entre 1 y 20\n");
        return NULL;
    }

    DatosMemoria *datos = (DatosMemoria*)malloc(sizeof(DatosMemoria));
    if (datos == NULL) {
        fprintf(stderr, "Error: No se pudo reservar memoria para DatosMemoria\n");
        return NULL;
    }

    datos->total_rondas = num_rondas;
    datos->aciertos = 0;
    datos->longitud_maxima = 0;
    datos->capacidad_secuencia = capacidad_secuencia;

    datos->secuencia_correcta = (int*)malloc(capacidad_secuencia * sizeof(int));
    if (datos->secuencia_correcta == NULL) {
        free(datos);
        return NULL;
    }

    datos->secuencia_usuario = (int*)malloc(capacidad_secuencia * sizeof(int));
    if (datos->secuencia_usuario == NULL) {
        free(datos->secuencia_correcta);
        free(datos);
        return NULL;
    }

    for (int i = 0; i < capacidad_secuencia; i++) {
        datos->secuencia_correcta[i] = 0;
        datos->secuencia_usuario[i] = 0;
    }

    return datos;
}

void liberar_datos_memoria(DatosMemoria *datos) {
    if (datos == NULL) return;

    if (datos->secuencia_usuario != NULL) free(datos->secuencia_usuario);
    if (datos->secuencia_correcta != NULL) free(datos->secuencia_correcta);
    free(datos);
}

// ============================================================================
// EJERCICIO 1: REFLEJOS - MANO DERECHA
// ============================================================================

void ejercicio_reflejos_mano_derecha() {
    limpiar_pantalla();
    printf("=====================================\n");
    printf("    🎯 REFLEJOS - MANO DERECHA\n");
    printf("=====================================\n");
    printf("Instrucciones:\n");
    printf("- Usa solo tu MANO DERECHA\n");
    printf("- Cuando veas una letra, presiónala inmediatamente\n");
    printf("- ¡Mide tu tiempo de reacción!\n");

    int num_intentos;
    printf("\n¿Cuántos intentos quieres hacer? (1-50, recomendado 7): ");

    if (scanf("%d", &num_intentos) != 1 || num_intentos <= 0 || num_intentos > 50) {
        printf("❌ Número inválido. Usando 7 intentos por defecto.\n");
        num_intentos = 7;
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    printf("\nPresiona ENTER para comenzar...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    DatosReflejos *datos = crear_datos_reflejos(num_intentos);
    if (datos == NULL) {
        printf("❌ Error al inicializar el ejercicio.\n");
        pausa_ms(2000);
        return;
    }

    for (int i = 0; i < datos->total_intentos; i++) {
        limpiar_pantalla();
        printf("Reflejos - Mano Derecha | Intento %d/%d\n", i+1, datos->total_intentos);
        printf("=====================================\n");

        char letra_objetivo = TECLAS_MANO_DERECHA[rand() % NUM_TECLAS];
        datos->teclas_correctas[i] = letra_objetivo;

        printf("\n\n\n      🎯 PREPARADO...\n");
        pausa_ms(1500);

        printf("\n\n\n         💥 %c 💥\n", letra_objetivo);
        printf("     ¡PRESIONA LA TECLA!\n\n");

        double inicio = obtener_tiempo_actual_alta_precision();

        system("stty raw -echo");
        char tecla_presionada = getchar();
        system("stty cooked echo");

        double fin = obtener_tiempo_actual_alta_precision();
        double tiempo_reaccion = (fin - inicio) * 1000;

        datos->teclas_presionadas[i] = tecla_presionada;
        datos->tiempos[i] = tiempo_reaccion;

        if (tecla_presionada == letra_objetivo) {
            printf("     ✅ CORRECTO!\n");
            datos->aciertos++;
        } else {
            printf("     ❌ ERROR: Presionaste '%c', era '%c'\n",
                   tecla_presionada, letra_objetivo);
        }

        printf("     Tiempo: %.0f ms\n", tiempo_reaccion);

        if (i < datos->total_intentos - 1) {
            printf("\nPreparando siguiente letra...\n");
            pausa_ms(2000);
        }
    }

    mostrar_estadisticas_reflejos(datos);
    liberar_datos_reflejos(datos);
}

void mostrar_estadisticas_reflejos(DatosReflejos *datos) {
    if (datos == NULL) return;

    limpiar_pantalla();
    printf("=====================================\n");
    printf("         📊 ESTADÍSTICAS\n");
    printf("=====================================\n");

    double suma_tiempos = 0;
    double mejor_tiempo = 9999;
    int tiempos_validos = 0;

    printf("\nTiempos por intento:\n");
    for (int i = 0; i < datos->total_intentos; i++) {
        printf("Intento %d [%c → %c]: ", i+1,
               datos->teclas_correctas[i],
               datos->teclas_presionadas[i]);

        if (datos->teclas_presionadas[i] == datos->teclas_correctas[i]) {
            printf("%.0f ms ✅\n", datos->tiempos[i]);
            suma_tiempos += datos->tiempos[i];
            tiempos_validos++;
            if (datos->tiempos[i] < mejor_tiempo) {
                mejor_tiempo = datos->tiempos[i];
            }
        } else {
            printf("Error ❌\n");
        }
    }

    printf("\n--- RESUMEN ---\n");
    printf("Aciertos: %d/%d (%.1f%%)\n",
           datos->aciertos, datos->total_intentos,
           (datos->aciertos * 100.0) / datos->total_intentos);

    if (tiempos_validos > 0) {
        double promedio = suma_tiempos / tiempos_validos;
        printf("Tiempo promedio: %.0f ms\n", promedio);
        printf("Mejor tiempo: %.0f ms\n", mejor_tiempo);

        printf("\n🏆 EVALUACIÓN:\n");
        if (promedio < 300) printf("¡Excelente! Reflejos de halcón 🦅\n");
        else if (promedio < 500) printf("Muy bueno, sigue practicando 💪\n");
        else if (promedio < 800) printf("Bien, hay espacio para mejorar 📈\n");
        else printf("Sigue practicando, mejorarás 🎯\n");
    }

    printf("\nPresiona ENTER para volver al menú...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
}

// ============================================================================
// EJERCICIO 2: CAZA DE CARACTERES
// ============================================================================

void ejercicio_caza_caracteres() {
    limpiar_pantalla();
    printf("=====================================\n");
    printf("       ⚡ CAZA DE CARACTERES ⚡\n");
    printf("=====================================\n");
    printf("Instrucciones:\n");
    printf("- Los caracteres aparecerán en pantalla\n");
    printf("- Debes escribirlos rápidamente\n");
    printf("- Tienes 3 segundos por carácter\n");
    printf("- ¡Coordina tus ojos y manos!\n");

    int num_rondas;
    printf("\n¿Cuántas rondas quieres hacer? (1-20, recomendado 5): ");

    if (scanf("%d", &num_rondas) != 1 || num_rondas <= 0 || num_rondas > 20) {
        printf("❌ Número inválido. Usando 5 rondas por defecto.\n");
        num_rondas = 5;
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    printf("\nPresiona ENTER para comenzar...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    DatosCazaCaracteres *datos = crear_datos_caza(num_rondas);
    if (datos == NULL) {
        printf("❌ Error al inicializar el ejercicio.\n");
        pausa_ms(2000);
        return;
    }

    char caracteres[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%&";
    int num_caracteres = 42;

    for (int ronda = 0; ronda < datos->total_rondas; ronda++) {
        limpiar_pantalla();
        printf("Caza de Caracteres | Ronda %d/%d\n", ronda + 1, datos->total_rondas);
        printf("=====================================\n");

        char caracter_objetivo = caracteres[rand() % num_caracteres];
        datos->caracteres_objetivo[ronda] = caracter_objetivo;

        printf("\n\n🎯 El carácter aparecerá en...\n");
        for (int i = 3; i > 0; i--) {
            printf("   %d...\n", i);
            pausa_ms(800);
        }

        limpiar_pantalla();
        printf("Caza de Caracteres | Ronda %d/%d\n", ronda + 1, datos->total_rondas);
        printf("=====================================\n");

        int espacios_izquierda = 10 + (rand() % 40);
        int espacios_arriba = 3 + (rand() % 8);

        for (int i = 0; i < espacios_arriba; i++) printf("\n");
        for (int i = 0; i < espacios_izquierda; i++) printf(" ");

        printf("╔═════════╗\n");
        for (int i = 0; i < espacios_izquierda; i++) printf(" ");
        printf("║    %c    ║\n", caracter_objetivo);
        for (int i = 0; i < espacios_izquierda; i++) printf(" ");
        printf("╚═════════╝\n");

        printf("\n\n¡ESCRIBE EL CARÁCTER! (Tienes 3 segundos)\n");

        double inicio = obtener_tiempo_actual_alta_precision();
        char tecla_presionada = '\0';
        int caracter_leido = 0;

        double tiempo_transcurrido = 0;
        while (tiempo_transcurrido < 3.0) {
            system("stty raw -echo");
            struct timeval tv = {0, 100000};
            fd_set fds;
            FD_ZERO(&fds);
            FD_SET(0, &fds);

            if (select(1, &fds, NULL, NULL, &tv) > 0) {
                tecla_presionada = getchar();
                caracter_leido = 1;
                break;
            }
            system("stty cooked echo");

            double tiempo_actual = obtener_tiempo_actual_alta_precision();
            tiempo_transcurrido = tiempo_actual - inicio;
        }
        system("stty cooked echo");

        double fin = obtener_tiempo_actual_alta_precision();
        double tiempo_reaccion = (fin - inicio) * 1000;

        datos->caracteres_presionados[ronda] = tecla_presionada;
        datos->tiempos[ronda] = tiempo_reaccion;

        limpiar_pantalla();
        printf("Caza de Caracteres | Ronda %d/%d\n", ronda + 1, datos->total_rondas);
        printf("=====================================\n");

        if (caracter_leido && tecla_presionada == caracter_objetivo && tiempo_reaccion <= 3000) {
            printf("✅ ¡ATRAPADO! Carácter: %c\n", caracter_objetivo);
            printf("   Tiempo: %.0f ms\n", tiempo_reaccion);
            datos->aciertos++;
        } else if (tiempo_reaccion > 3000) {
            printf("❌ ¡SE ESCAPÓ! Carácter: %c\n", caracter_objetivo);
            printf("   Te demoraste demasiado (%.0f ms)\n", tiempo_reaccion);
            datos->tiempos[ronda] = -1;
        } else if (caracter_leido && tecla_presionada != caracter_objetivo) {
            printf("❌ ERROR: Presionaste '%c', era '%c'\n",
                   tecla_presionada, caracter_objetivo);
            printf("   Tiempo: %.0f ms\n", tiempo_reaccion);
            datos->tiempos[ronda] = -1;
        } else {
            printf("❌ NO RESPONDISTE: Era '%c'\n", caracter_objetivo);
            datos->tiempos[ronda] = -1;
        }

        if (ronda < datos->total_rondas - 1) {
            printf("\nPreparando siguiente carácter...\n");
            pausa_ms(2000);
        }
    }

    mostrar_estadisticas_caza(datos);
    liberar_datos_caza(datos);
}

void mostrar_estadisticas_caza(DatosCazaCaracteres *datos) {
    if (datos == NULL) return;

    limpiar_pantalla();
    printf("=====================================\n");
    printf("       📊 ESTADÍSTICAS CAZA\n");
    printf("=====================================\n");

    double suma_tiempos = 0;
    double mejor_tiempo = 9999;
    int tiempos_validos = 0;

    printf("\nResultados por ronda:\n");
    for (int i = 0; i < datos->total_rondas; i++) {
        printf("Ronda %d [%c → %c]: ", i + 1,
               datos->caracteres_objetivo[i],
               datos->caracteres_presionados[i]);

        if (datos->tiempos[i] > 0 && datos->tiempos[i] <= 3000) {
            printf("%.0f ms ✅\n", datos->tiempos[i]);
            suma_tiempos += datos->tiempos[i];
            tiempos_validos++;
            if (datos->tiempos[i] < mejor_tiempo) {
                mejor_tiempo = datos->tiempos[i];
            }
        } else if (datos->tiempos[i] > 3000) {
            printf("Tiempo agotado ❌\n");
        } else {
            printf("Error ❌\n");
        }
    }

    printf("\n--- RESUMEN ---\n");
    printf("Caracteres atrapados: %d/%d (%.1f%%)\n",
           datos->aciertos, datos->total_rondas,
           (datos->aciertos * 100.0) / datos->total_rondas);

    if (tiempos_validos > 0) {
        double promedio = suma_tiempos / tiempos_validos;
        printf("Tiempo promedio: %.0f ms\n", promedio);
        printf("Mejor tiempo: %.0f ms\n", mejor_tiempo);

        printf("\n🏆 EVALUACIÓN:\n");
        if (promedio < 1500 && datos->aciertos == datos->total_rondas)
            printf("¡Excelente! Ojos de águila 🦅\n");
        else if (promedio < 2000 && datos->aciertos >= datos->total_rondas - 1)
            printf("Muy bueno, coordinación perfecta 💪\n");
        else if (datos->aciertos >= datos->total_rondas - 2)
            printf("Bien, sigue practicando 📈\n");
        else
            printf("Sigue entrenando, mejorarás 🎯\n");
    }

    printf("\nPresiona ENTER para volver al menú...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
}

// Continuará en la siguiente parte...
// ============================================================================
// EJERCICIO 3: CÁLCULO MENTAL
// ============================================================================

void ejercicio_calculo_mental() {
    limpiar_pantalla();
    printf("=====================================\n");
    printf("         🧮 CÁLCULO MENTAL 🧮\n");
    printf("=====================================\n");
    printf("Instrucciones:\n");
    printf("- Resuelve operaciones matemáticas mentalmente\n");
    printf("- Tienes tiempo limitado por operación\n");
    printf("- +1 punto por acierto, bonus por velocidad\n");
    printf("- ¡Desafía tu agilidad numérica!\n");

    int num_operaciones;
    printf("\n¿Cuántas operaciones quieres hacer? (1-20, recomendado 8): ");

    if (scanf("%d", &num_operaciones) != 1 || num_operaciones <= 0 || num_operaciones > 20) {
        printf("❌ Número inválido. Usando 8 operaciones por defecto.\n");
        num_operaciones = 8;
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    printf("\nPresiona ENTER para comenzar...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    DatosCalculo *datos = crear_datos_calculo(num_operaciones);
    if (datos == NULL) {
        printf("❌ Error al inicializar el ejercicio.\n");
        pausa_ms(2000);
        return;
    }

    int nivel_actual = 1;
    int operaciones_por_nivel = 2;

    for (int op = 0; op < datos->total_operaciones; op++) {
        if (op > 0 && op % operaciones_por_nivel == 0) {
            nivel_actual++;
            if (nivel_actual > 4) nivel_actual = 4;  // Máximo nivel 4
        }

        limpiar_pantalla();
        printf("Cálculo Mental | Op %d/%d | Nivel %d\n",
               op + 1, datos->total_operaciones, nivel_actual);
        printf("=====================================\n");

        int a, b, resultado_correcto;
        char operador;
        int tiempo_limite;

        generar_operacion(nivel_actual, &a, &b, &operador, &resultado_correcto, &tiempo_limite);

        printf("\n\n    ");
        if (operador == '+' || operador == '-' || operador == '*') {
            printf("%2d %c %2d = ?", a, operador, b);
        } else {
            printf("(%d %c %d) = ?", a, operador, b);
        }

        printf("\n\n    Tiempo límite: %d segundos\n", tiempo_limite);
        printf("\n    Tu respuesta: ");
        fflush(stdout);

        double inicio = obtener_tiempo_actual_alta_precision();

        int respuesta_usuario;
        int leido = 0;
        double tiempo_transcurrido = 0;

        while (tiempo_transcurrido < tiempo_limite) {
            if (scanf("%d", &respuesta_usuario) == 1) {
                leido = 1;
                break;
            }

            while ((c = getchar()) != '\n' && c != EOF);

            double tiempo_actual = obtener_tiempo_actual_alta_precision();
            tiempo_transcurrido = tiempo_actual - inicio;
        }

        double fin = obtener_tiempo_actual_alta_precision();
        double tiempo_respuesta = (fin - inicio) * 1000;

        while ((c = getchar()) != '\n' && c != EOF);

        limpiar_pantalla();
        printf("Cálculo Mental | Op %d/%d | Nivel %d\n",
               op + 1, datos->total_operaciones, nivel_actual);
        printf("=====================================\n");

        if (leido && respuesta_usuario == resultado_correcto && tiempo_respuesta <= tiempo_limite * 1000) {
            printf("✅ ¡CORRECTO! %d %c %d = %d\n", a, operador, b, resultado_correcto);
            printf("   Tiempo: %.0f ms\n", tiempo_respuesta);

            int puntos_base = nivel_actual * 10;
            double factor_velocidad = 1.0 - (tiempo_respuesta / (tiempo_limite * 2000.0));
            int puntos_extra = (int)(puntos_base * factor_velocidad);
            if (puntos_extra < 0) puntos_extra = 0;
            int puntos_ronda = puntos_base + puntos_extra;

            printf("   Puntos: +%d (%d base + %d velocidad)\n",
                   puntos_ronda, puntos_base, puntos_extra);

            datos->puntuacion += puntos_ronda;
            datos->aciertos++;
            datos->tiempos[op] = tiempo_respuesta;
        } else if (tiempo_respuesta > tiempo_limite * 1000) {
            printf("❌ ¡TIEMPO AGOTADO! %d %c %d = %d\n", a, operador, b, resultado_correcto);
            datos->tiempos[op] = -1;
        } else if (leido && respuesta_usuario != resultado_correcto) {
            printf("❌ ERROR: Dijiste %d, era %d\n", respuesta_usuario, resultado_correcto);
            printf("   %d %c %d = %d\n", a, operador, b, resultado_correcto);
            datos->tiempos[op] = -1;
        } else {
            printf("❌ NO RESPONDISTE: %d %c %d = %d\n", a, operador, b, resultado_correcto);
            datos->tiempos[op] = -1;
        }

        if (op < datos->total_operaciones - 1) {
            printf("\nSiguiente operación en 2 segundos...\n");
            pausa_ms(2000);
        }
    }

    mostrar_estadisticas_calculo(datos);
    liberar_datos_calculo(datos);
}

void generar_operacion(int nivel, int *a, int *b, char *operador, int *resultado, int *tiempo_limite) {
    switch(nivel) {
        case 1: // Sumas y restas básicas
            *a = 1 + rand() % 20;
            *b = 1 + rand() % 20;
            *operador = (rand() % 2 == 0) ? '+' : '-';
            *tiempo_limite = 8;
            break;

        case 2: // Multiplicaciones simples
            *a = 2 + rand() % 12;
            *b = 2 + rand() % 12;
            *operador = '*';
            *tiempo_limite = 10;
            break;

        case 3: // Operaciones combinadas
            if(rand() % 2 == 0) {
                *a = 10 + rand() % 40;
                *b = 2 + rand() % 9;
                *operador = (rand() % 2 == 0) ? '+' : '-';
            } else {
                *a = 3 + rand() % 15;
                *b = 3 + rand() % 8;
                *operador = '*';
            }
            *tiempo_limite = 12;
            break;

        case 4: // Operaciones complejas
            *a = 20 + rand() % 50;
            *b = 5 + rand() % 25;
            *operador = (rand() % 3 == 0) ? '+' : (rand() % 2 == 0) ? '-' : '*';
            *tiempo_limite = 15;
            break;
    }

    // Calcular resultado
    switch(*operador) {
        case '+': *resultado = *a + *b; break;
        case '-':
            if(*a < *b) { int temp = *a; *a = *b; *b = temp; }
            *resultado = *a - *b;
            break;
        case '*': *resultado = *a * *b; break;
    }
}

void mostrar_estadisticas_calculo(DatosCalculo *datos) {
    if (datos == NULL) return;

    limpiar_pantalla();
    printf("=====================================\n");
    printf("     📊 ESTADÍSTICAS CÁLCULO\n");
    printf("=====================================\n");

    double suma_tiempos = 0;
    double mejor_tiempo = 9999;
    int tiempos_validos = 0;

    printf("\nResultados por operación:\n");
    for (int i = 0; i < datos->total_operaciones; i++) {
        printf("Op %d: ", i + 1);
        if (datos->tiempos[i] > 0) {
            printf("%.0f ms ✅\n", datos->tiempos[i]);
            suma_tiempos += datos->tiempos[i];
            tiempos_validos++;
            if (datos->tiempos[i] < mejor_tiempo) {
                mejor_tiempo = datos->tiempos[i];
            }
        } else {
            printf("Error/Tiempo ❌\n");
        }
    }

    printf("\n--- RESUMEN ---\n");
    printf("Aciertos: %d/%d (%.1f%%)\n",
           datos->aciertos, datos->total_operaciones,
           (datos->aciertos * 100.0) / datos->total_operaciones);
    printf("Puntuación total: %d puntos\n", datos->puntuacion);

    if (tiempos_validos > 0) {
        double promedio = suma_tiempos / tiempos_validos;
        printf("Tiempo promedio: %.0f ms\n", promedio);
        printf("Mejor tiempo: %.0f ms\n", mejor_tiempo);

        printf("\n🏆 EVALUACIÓN:\n");
        if (datos->puntuacion >= 300)
            printf("¡GENIO MATEMÁTICO! 🧠\n");
        else if (datos->puntuacion >= 200)
            printf("Excelente cálculo mental 💪\n");
        else if (datos->puntuacion >= 100)
            printf("Buen trabajo, sigue practicando 📈\n");
        else
            printf("Sigue entrenando, mejorarás 🎯\n");

        printf("\n💡 Tip: Practica diariamente para mejorar tu velocidad\n");
    }

    printf("\nPresiona ENTER para volver al menú...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
}

// ============================================================================
// EJERCICIO 4: MEMORIA DE NÚMEROS
// ============================================================================

void ejercicio_memoria_numeros() {
    limpiar_pantalla();
    printf("=====================================\n");
    printf("       🔢 MEMORIA DE NÚMEROS 🔢\n");
    printf("=====================================\n");
    printf("Instrucciones:\n");
    printf("- Memoriza la secuencia de números\n");
    printf("- Luego repítela en el mismo orden\n");
    printf("- La longitud aumenta cada 2 rondas\n");
    printf("- ¡Ejercita tu memoria a corto plazo!\n");

    int num_rondas;
    printf("\n¿Cuántas rondas quieres hacer? (1-10, recomendado 5): ");

    if (scanf("%d", &num_rondas) != 1 || num_rondas <= 0 || num_rondas > 10) {
        printf("❌ Número inválido. Usando 5 rondas por defecto.\n");
        num_rondas = 5;
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    printf("\nPresiona ENTER para comenzar...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    // Capacidad máxima de 10 números (más que suficiente)
    DatosMemoria *datos = crear_datos_memoria(num_rondas, 10);
    if (datos == NULL) {
        printf("❌ Error al inicializar el ejercicio.\n");
        pausa_ms(2000);
        return;
    }

    for (int ronda = 0; ronda < datos->total_rondas; ronda++) {
        // Determinar longitud de la secuencia (4-10 números)
        int longitud_secuencia = 4 + (ronda / 2);
        if (longitud_secuencia > datos->capacidad_secuencia) {
            longitud_secuencia = datos->capacidad_secuencia;
        }

        if (longitud_secuencia > datos->longitud_maxima) {
            datos->longitud_maxima = longitud_secuencia;
        }

        limpiar_pantalla();
        printf("Memoria de Números | Ronda %d/%d\n", ronda + 1, datos->total_rondas);
        printf("=====================================\n");
        printf("Longitud de secuencia: %d números\n\n", longitud_secuencia);

        // Generar secuencia aleatoria
        printf("🎯 MEMORIZA ESTA SECUENCIA:\n\n");
        printf("    ");
        for (int i = 0; i < longitud_secuencia; i++) {
            datos->secuencia_correcta[i] = rand() % 10;
            printf("%d ", datos->secuencia_correcta[i]);
        }
        printf("\n\n");

        // Tiempo para memorizar
        int tiempo_memorizacion = 3 + (longitud_secuencia * 2);
        printf("Tienes %d segundos para memorizar...\n", tiempo_memorizacion);

        for (int i = tiempo_memorizacion; i > 0; i--) {
            printf("%d... ", i);
            fflush(stdout);
            pausa_ms(1000);
        }

        limpiar_pantalla();
        printf("Memoria de Números | Ronda %d/%d\n", ronda + 1, datos->total_rondas);
        printf("=====================================\n");
        printf("Longitud: %d números\n\n", longitud_secuencia);

        // Leer la secuencia del usuario
        printf("🔁 REPITE LA SECUENCIA (escribe los números separados por espacios):\n\n");
        printf("    ");

        int secuencia_correcta_flag = 1;
        for (int i = 0; i < longitud_secuencia; i++) {
            int numero;
            if (scanf("%d", &numero) == 1) {
                datos->secuencia_usuario[i] = numero;
                if (numero != datos->secuencia_correcta[i]) {
                    secuencia_correcta_flag = 0;
                }
            } else {
                secuencia_correcta_flag = 0;
                break;
            }
        }

        // Limpiar buffer
        while ((c = getchar()) != '\n' && c != EOF);

        // Mostrar resultados
        limpiar_pantalla();
        printf("Memoria de Números | Ronda %d/%d\n", ronda + 1, datos->total_rondas);
        printf("=====================================\n");

        if (secuencia_correcta_flag) {
            printf("✅ ¡SECUENCIA CORRECTA!\n\n");
            printf("Secuencia original: ");
            for (int i = 0; i < longitud_secuencia; i++) {
                printf("%d ", datos->secuencia_correcta[i]);
            }
            printf("\nTu respuesta:       ");
            for (int i = 0; i < longitud_secuencia; i++) {
                printf("%d ", datos->secuencia_usuario[i]);
            }
            printf("\n\n¡Memoria excelente! 🧠\n");
            datos->aciertos++;
        } else {
            printf("❌ SECUENCIA INCORRECTA\n\n");
            printf("Secuencia original: ");
            for (int i = 0; i < longitud_secuencia; i++) {
                printf("%d ", datos->secuencia_correcta[i]);
            }
            printf("\nTu respuesta:       ");
            for (int i = 0; i < longitud_secuencia; i++) {
                printf("%d ", datos->secuencia_usuario[i]);
            }
            printf("\n\n💡 Tip: Concéntrate en grupos de 2-3 números\n");
        }

        if (ronda < datos->total_rondas - 1) {
            printf("\nSiguiente ronda en 3 segundos...\n");
            pausa_ms(3000);
        }
    }

    mostrar_estadisticas_memoria(datos);
    liberar_datos_memoria(datos);
}

void mostrar_estadisticas_memoria(DatosMemoria *datos) {
    if (datos == NULL) return;

    limpiar_pantalla();
    printf("=====================================\n");
    printf("    📊 ESTADÍSTICAS MEMORIA\n");
    printf("=====================================\n");

    printf("\n--- RESUMEN ---\n");
    printf("Rondas completadas: %d/%d\n", datos->total_rondas, datos->total_rondas);
    printf("Secuencias correctas: %d/%d (%.1f%%)\n",
           datos->aciertos, datos->total_rondas,
           (datos->aciertos * 100.0) / datos->total_rondas);
    printf("Longitud máxima alcanzada: %d números\n", datos->longitud_maxima);

    // Evaluación
    printf("\n🏆 EVALUACIÓN:\n");
    if (datos->aciertos == datos->total_rondas && datos->longitud_maxima >= 6) {
        printf("¡MEMORIA FOTOGRÁFICA! 📸\n");
        printf("Tu memoria a corto plazo es excelente\n");
    } else if (datos->aciertos >= datos->total_rondas - 1) {
        printf("¡MEMORIA SOBRESALIENTE! 💪\n");
        printf("Muy buena retención de información\n");
    } else if (datos->aciertos >= datos->total_rondas - 2) {
        printf("BUENA MEMORIA 📈\n");
        printf("Sigue practicando para mejorar\n");
    } else {
        printf("MEMORIA EN ENTRENAMIENTO 🎯\n");
        printf("La práctica constante te hará mejorar\n");
    }

    // Tips según el desempeño
    printf("\n💡 TIPS PARA MEJORAR:\n");
    if (datos->longitud_maxima < 5) {
        printf("- Agrupa números en pares (12 34 56)\n");
        printf("- Asocia números con imágenes mentales\n");
    } else if (datos->longitud_maxima < 7) {
        printf("- Usa el método de loci (palacio mental)\n");
        printf("- Crea historias con los números\n");
    } else {
        printf("- Desafíate con secuencias de 8+ números\n");
        printf("- Practica con intervalos de tiempo mayores\n");
    }

    printf("\nPresiona ENTER para volver al menú...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
}




// ============================================================================
// FUNCIONES DE GESTIÓN DE MEMORIA - STROOP TEST
// ============================================================================

DatosStroop* crear_datos_stroop(int num_rondas) {
    if (num_rondas <= 0 || num_rondas > 100) {
        fprintf(stderr, "Error: num_rondas debe estar entre 1 y 100\n");
        return NULL;
    }

    DatosStroop *datos = (DatosStroop*)malloc(sizeof(DatosStroop));
    if (datos == NULL) {
        fprintf(stderr, "Error: No se pudo reservar memoria para DatosStroop\n");
        return NULL;
    }

    datos->total_rondas = num_rondas;
    datos->aciertos = 0;
    datos->errores_congruentes = 0;
    datos->errores_incongruentes = 0;

    datos->tiempos = (double*)malloc(num_rondas * sizeof(double));
    if (datos->tiempos == NULL) {
        free(datos);
        return NULL;
    }

    datos->fue_congruente = (int*)malloc(num_rondas * sizeof(int));
    if (datos->fue_congruente == NULL) {
        free(datos->tiempos);
        free(datos);
        return NULL;
    }

    datos->fue_correcto = (int*)malloc(num_rondas * sizeof(int));
    if (datos->fue_correcto == NULL) {
        free(datos->fue_congruente);
        free(datos->tiempos);
        free(datos);
        return NULL;
    }

    for (int i = 0; i < num_rondas; i++) {
        datos->tiempos[i] = -1.0;
        datos->fue_congruente[i] = 0;
        datos->fue_correcto[i] = 0;
    }

    return datos;
}

void liberar_datos_stroop(DatosStroop *datos) {
    if (datos == NULL) return;

    if (datos->fue_correcto != NULL) free(datos->fue_correcto);
    if (datos->fue_congruente != NULL) free(datos->fue_congruente);
    if (datos->tiempos != NULL) free(datos->tiempos);
    free(datos);
}

// ============================================================================
// EJERCICIO 5: STROOP TEST
// ============================================================================

// Definición de colores y palabras
typedef struct {
    const char *nombre;      // Nombre del color
    const char *codigo_ansi; // Código ANSI para imprimir en ese color
    char tecla;              // Tecla que representa el color
} ColorInfo;

// Tabla de colores disponibles
static const ColorInfo COLORES[] = {
    {"ROJO",     "\033[31m", 'R'},  // Rojo
    {"VERDE",    "\033[32m", 'V'},  // Verde
    {"AZUL",     "\033[34m", 'A'},  // Azul
    {"AMARILLO", "\033[33m", 'M'},  // Amarillo (aMarillo para evitar conflicto con Azul)
};
static const int NUM_COLORES = 4;
static const char *RESET_COLOR = "\033[0m";

void ejercicio_stroop_test() {
    limpiar_pantalla();
    printf("=====================================\n");
    printf("         🎨 STROOP TEST 🎨\n");
    printf("=====================================\n");
    printf("Instrucciones:\n");
    printf("- Verás palabras de COLORES escritas en diferentes colores\n");
    printf("- Debes identificar el COLOR de la tinta, NO la palabra\n");
    printf("- Ejemplo: 'ROJO' escrito en azul → presiona 'A' (azul)\n");
    printf("- ¡Entrena tu control inhibitorio!\n\n");

    printf("Teclas:\n");
    printf("  R = Rojo\n");
    printf("  V = Verde\n");
    printf("  A = Azul\n");
    printf("  M = Amarillo\n");

    int num_rondas;
    printf("\n¿Cuántas rondas quieres hacer? (1-30, recomendado 15): ");

    if (scanf("%d", &num_rondas) != 1 || num_rondas <= 0 || num_rondas > 30) {
        printf("❌ Número inválido. Usando 15 rondas por defecto.\n");
        num_rondas = 15;
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    printf("\nPresiona ENTER para comenzar...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    DatosStroop *datos = crear_datos_stroop(num_rondas);
    if (datos == NULL) {
        printf("❌ Error al inicializar el ejercicio.\n");
        pausa_ms(2000);
        return;
    }

    // Mezcla de trials congruentes (50%) e incongruentes (50%)
    int rondas_congruentes = num_rondas / 2;
    int rondas_incongruentes = num_rondas - rondas_congruentes;

    for (int ronda = 0; ronda < datos->total_rondas; ronda++) {
        limpiar_pantalla();
        printf("Stroop Test | Ronda %d/%d\n", ronda + 1, datos->total_rondas);
        printf("=====================================\n");

        // Decidir si esta ronda es congruente o incongruente
        int es_congruente;
        if (ronda < rondas_congruentes) {
            es_congruente = 1;
        } else {
            es_congruente = 0;
        }

        // Mezclar para que no sean predecibles
        if (rand() % 2 == 0 && ronda > 0) {
            es_congruente = !es_congruente;
        }

        datos->fue_congruente[ronda] = es_congruente;

        int idx_palabra, idx_color;

        if (es_congruente) {
            // Congruente: palabra y color coinciden
            idx_palabra = rand() % NUM_COLORES;
            idx_color = idx_palabra;
        } else {
            // Incongruente: palabra y color diferentes
            idx_palabra = rand() % NUM_COLORES;
            do {
                idx_color = rand() % NUM_COLORES;
            } while (idx_color == idx_palabra);
        }

        const char *palabra = COLORES[idx_palabra].nombre;
        const char *color_codigo = COLORES[idx_color].codigo_ansi;
        char tecla_correcta = COLORES[idx_color].tecla;

        // Cuenta regresiva
        printf("\n\n🎯 Preparado...\n");
        pausa_ms(1000);

        limpiar_pantalla();
        printf("Stroop Test | Ronda %d/%d\n", ronda + 1, datos->total_rondas);
        printf("=====================================\n");

        // Mostrar el estímulo Stroop
        printf("\n\n\n");
        printf("         ╔═══════════════╗\n");
        printf("         ║               ║\n");
        printf("         ║   %s%s%s   ║\n", color_codigo, palabra, RESET_COLOR);
        printf("         ║               ║\n");
        printf("         ╚═══════════════╝\n");
        printf("\n\n");
        printf("    ¿Qué COLOR ves? (R/V/A/M): ");
        fflush(stdout);

        double inicio = obtener_tiempo_actual_alta_precision();

        // Leer respuesta
        system("stty raw -echo");
        char tecla_presionada = getchar();
        system("stty cooked echo");

        // Convertir a mayúscula
        if (tecla_presionada >= 'a' && tecla_presionada <= 'z') {
            tecla_presionada = tecla_presionada - 'a' + 'A';
        }

        double fin = obtener_tiempo_actual_alta_precision();
        double tiempo_reaccion = (fin - inicio) * 1000;

        datos->tiempos[ronda] = tiempo_reaccion;

        // Verificar respuesta
        limpiar_pantalla();
        printf("Stroop Test | Ronda %d/%d\n", ronda + 1, datos->total_rondas);
        printf("=====================================\n");

        printf("\nPalabra mostrada: %s\n", palabra);
        printf("Color de la tinta: %s%s%s\n", color_codigo, COLORES[idx_color].nombre, RESET_COLOR);
        printf("Respuesta correcta: %c (%s)\n", tecla_correcta, COLORES[idx_color].nombre);
        printf("Tu respuesta: %c\n", tecla_presionada);
        printf("Tiempo: %.0f ms\n\n", tiempo_reaccion);

        if (tecla_presionada == tecla_correcta) {
            printf("✅ ¡CORRECTO!\n");
            datos->aciertos++;
            datos->fue_correcto[ronda] = 1;
        } else {
            printf("❌ ERROR\n");
            datos->fue_correcto[ronda] = 0;

            // Contar tipo de error
            if (es_congruente) {
                datos->errores_congruentes++;
            } else {
                datos->errores_incongruentes++;
            }
        }

        if (es_congruente) {
            printf("Tipo: CONGRUENTE (fácil)\n");
        } else {
            printf("Tipo: INCONGRUENTE (difícil)\n");
        }

        if (ronda < datos->total_rondas - 1) {
            printf("\nSiguiente en 2 segundos...\n");
            pausa_ms(2000);
        }
    }

    mostrar_estadisticas_stroop(datos);
    liberar_datos_stroop(datos);
}

void mostrar_estadisticas_stroop(DatosStroop *datos) {
    if (datos == NULL) return;

    limpiar_pantalla();
    printf("=====================================\n");
    printf("      📊 ESTADÍSTICAS STROOP\n");
    printf("=====================================\n");

    // Calcular estadísticas separadas
    double suma_tiempos_congruente = 0, suma_tiempos_incongruente = 0;
    int aciertos_congruente = 0, aciertos_incongruente = 0;
    int count_congruente = 0, count_incongruente = 0;
    double mejor_tiempo = 9999;

    printf("\nResultados detallados:\n");
    for (int i = 0; i < datos->total_rondas; i++) {
        printf("Ronda %2d [%s]: ", i + 1,
               datos->fue_congruente[i] ? "CON" : "INC");

        if (datos->fue_correcto[i]) {
            printf("%.0f ms ✅\n", datos->tiempos[i]);

            if (datos->fue_congruente[i]) {
                suma_tiempos_congruente += datos->tiempos[i];
                aciertos_congruente++;
                count_congruente++;
            } else {
                suma_tiempos_incongruente += datos->tiempos[i];
                aciertos_incongruente++;
                count_incongruente++;
            }

            if (datos->tiempos[i] < mejor_tiempo) {
                mejor_tiempo = datos->tiempos[i];
            }
        } else {
            printf("Error ❌\n");

            if (datos->fue_congruente[i]) {
                count_congruente++;
            } else {
                count_incongruente++;
            }
        }
    }

    printf("\n--- RESUMEN GENERAL ---\n");
    printf("Aciertos totales: %d/%d (%.1f%%)\n",
           datos->aciertos, datos->total_rondas,
           (datos->aciertos * 100.0) / datos->total_rondas);
    printf("Mejor tiempo: %.0f ms\n", mejor_tiempo);

    printf("\n--- ANÁLISIS POR TIPO ---\n");

    // Congruentes
    if (count_congruente > 0) {
        double promedio_congruente = suma_tiempos_congruente / aciertos_congruente;
        printf("CONGRUENTES (fáciles):\n");
        printf("  Aciertos: %d/%d (%.1f%%)\n",
               aciertos_congruente, count_congruente,
               (aciertos_congruente * 100.0) / count_congruente);
        if (aciertos_congruente > 0) {
            printf("  Tiempo promedio: %.0f ms\n", promedio_congruente);
        }
    }

    // Incongruentes
    if (count_incongruente > 0) {
        double promedio_incongruente = suma_tiempos_incongruente / aciertos_incongruente;
        printf("INCONGRUENTES (difíciles):\n");
        printf("  Aciertos: %d/%d (%.1f%%)\n",
               aciertos_incongruente, count_incongruente,
               (aciertos_incongruente * 100.0) / count_incongruente);
        if (aciertos_incongruente > 0) {
            printf("  Tiempo promedio: %.0f ms\n", promedio_incongruente);
        }
    }

    // Calcular "efecto Stroop" (diferencia de tiempos)
    if (aciertos_congruente > 0 && aciertos_incongruente > 0) {
        double promedio_congruente = suma_tiempos_congruente / aciertos_congruente;
        double promedio_incongruente = suma_tiempos_incongruente / aciertos_incongruente;
        double efecto_stroop = promedio_incongruente - promedio_congruente;

        printf("\n🧠 EFECTO STROOP:\n");
        printf("  Diferencia de tiempo: %.0f ms\n", efecto_stroop);
        printf("  (Cuánto más lento eres en trials difíciles)\n");

        if (efecto_stroop < 100) {
            printf("  ¡Excelente control inhibitorio! 🏆\n");
        } else if (efecto_stroop < 200) {
            printf("  Buen control, sigue practicando 💪\n");
        } else {
            printf("  Hay margen de mejora 📈\n");
        }
    }

    printf("\n🏆 EVALUACIÓN GENERAL:\n");
    double accuracy = (datos->aciertos * 100.0) / datos->total_rondas;

    if (accuracy >= 90 && mejor_tiempo < 800) {
        printf("¡MAESTRO DEL CONTROL INHIBITORIO! 🧠\n");
        printf("Tu función ejecutiva es excelente\n");
    } else if (accuracy >= 80) {
        printf("¡MUY BUEN CONTROL! 💪\n");
        printf("Tu corteza prefrontal está trabajando bien\n");
    } else if (accuracy >= 70) {
        printf("BUEN PROGRESO 📈\n");
        printf("Sigue practicando para mejorar tu control\n");
    } else {
        printf("EN ENTRENAMIENTO 🎯\n");
        printf("El Stroop es difícil - la práctica te hará mejorar\n");
    }

    printf("\n💡 TIP:\n");
    if (datos->errores_incongruentes > datos->errores_congruentes * 2) {
        printf("Tus errores son mayormente en trials incongruentes.\n");
        printf("Esto es normal - practica ignorar la palabra escrita.\n");
    } else {
        printf("Buen balance de errores. Intenta responder más rápido\n");
        printf("sin sacrificar precisión.\n");
    }

    printf("\nPresiona ENTER para volver al menú...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
}

