#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "game_logic.h"
#include "utils.h"

// Teclas que corresponden a la mano derecha en teclado QWERTY
const char TECLAS_MANO_DERECHA[] = "yuiophjklñnm,.-";
const int NUM_TECLAS = 15;

// Declaración forward para evitar warnings
void mostrar_estadisticas_reflejos(double tiempos[], int total_intentos, int aciertos);


void ejercicio_reflejos_mano_derecha() {
    limpiar_pantalla();
    printf("=====================================\n");
    printf("    🎯 REFLEJOS - MANO DERECHA\n");
    printf("=====================================\n");
    printf("Instrucciones:\n");
    printf("- Usa solo tu MANO DERECHA\n");
    printf("- Cuando veas una letra, presiónala inmediatamente\n");
    printf("- Se mostrarán 7 letras aleatorias\n");
    printf("- ¡Mide tu tiempo de reacción!\n");
    printf("\nPresiona ENTER para comenzar...");

    // Limpiar el buffer de entrada
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    int intentos = 7;
    double tiempos[intentos];
    int aciertos = 0;

    for(int i = 0; i < intentos; i++) {
        limpiar_pantalla();
        printf("Reflejos - Mano Derecha | Intento %d/%d\n", i+1, intentos);
        printf("=====================================\n");

        // Generar letra aleatoria
        char letra_objetivo = TECLAS_MANO_DERECHA[rand() % NUM_TECLAS];

        printf("\n\n\n      🎯 PREPARADO...\n");
        pausa_ms(1500); // Pausa de 1.5 segundos

        printf("\n\n\n         💥 %c 💥\n", letra_objetivo);
        printf("     ¡PRESIONA LA TECLA!\n\n");

        // USAR ALTA PRECISIÓN AQUÍ
        double inicio = obtener_tiempo_actual_alta_precision();

        // Leer la tecla presionada (sin esperar Enter)
        system("stty raw -echo");
        char tecla_presionada = getchar();
        system("stty cooked echo");

        // USAR ALTA PRECISIÓN AQUÍ TAMBIÉN
        double fin = obtener_tiempo_actual_alta_precision();
        double tiempo_reaccion = (fin - inicio) * 1000; // Convertir a milisegundos

        // Verificar si es correcta
        if(tecla_presionada == letra_objetivo) {
            printf("     ✅ CORRECTO!\n");
            aciertos++;
            tiempos[i] = tiempo_reaccion;
        } else {
            printf("     ❌ ERROR: Presionaste '%c', era '%c'\n",
                   tecla_presionada, letra_objetivo);
            tiempos[i] = -1; // Marcar error
        }

        printf("     Tiempo: %.0f ms\n", tiempo_reaccion);

        if(i < intentos - 1) {
            printf("\nPreparando siguiente letra...\n");
            pausa_ms(2000);
        }
    }

    // Mostrar estadísticas
    mostrar_estadisticas_reflejos(tiempos, intentos, aciertos);
}

void mostrar_estadisticas_reflejos(double tiempos[], int total_intentos, int aciertos) {
    limpiar_pantalla();
    printf("=====================================\n");
    printf("         📊 ESTADÍSTICAS\n");
    printf("=====================================\n");

    double suma_tiempos = 0;
    double mejor_tiempo = 9999;
    int tiempos_validos = 0;

    printf("\nTiempos por intento:\n");
    for(int i = 0; i < total_intentos; i++) {
        printf("Intento %d: ", i+1);
        if(tiempos[i] > 0) {
            printf("%.0f ms\n", tiempos[i]);
            suma_tiempos += tiempos[i];
            tiempos_validos++;
            if(tiempos[i] < mejor_tiempo) {
                mejor_tiempo = tiempos[i];
            }
        } else {
            printf("Error\n");
        }
    }

    printf("\n--- RESUMEN ---\n");
    printf("Aciertos: %d/%d (%.1f%%)\n",
           aciertos, total_intentos,
           (aciertos * 100.0) / total_intentos);

    if(tiempos_validos > 0) {
        double promedio = suma_tiempos / tiempos_validos;
        printf("Tiempo promedio: %.0f ms\n", promedio);
        printf("Mejor tiempo: %.0f ms\n", mejor_tiempo);

        // Evaluación
        printf("\n🏆 EVALUACIÓN:\n");
        if(promedio < 300) printf("¡Excelente! Reflejos de halcón 🦅\n");
        else if(promedio < 500) printf("Muy bueno, sigue practicando 💪\n");
        else if(promedio < 800) printf("Bien, hay espacio para mejorar 📈\n");
        else printf("Sigue practicando, mejorarás 🎯\n");
    }

    printf("\nPresiona ENTER para volver al menú...");

    // Limpiar buffer antes de esperar Enter
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
}

//----------------------------------------------------------------------------
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
    printf("\nPresiona ENTER para comenzar...");

    // Limpiar buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    int total_rondas = 5;
    int aciertos = 0;
    double tiempos[total_rondas];
    char caracteres[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%&";
    int num_caracteres = 42;

    for(int ronda = 0; ronda < total_rondas; ronda++) {
        limpiar_pantalla();
        printf("Caza de Caracteres | Ronda %d/%d\n", ronda + 1, total_rondas);
        printf("=====================================\n");

        // Generar carácter aleatorio
        char caracter_objetivo = caracteres[rand() % num_caracteres];

        // Mostrar cuenta regresiva
        printf("\n\n🎯 El carácter aparecerá en...\n");
        for(int i = 3; i > 0; i--) {
            printf("   %d...\n", i);
            pausa_ms(800);
        }

        limpiar_pantalla();
        printf("Caza de Caracteres | Ronda %d/%d\n", ronda + 1, total_rondas);
        printf("=====================================\n");

        // Mostrar el carácter objetivo en posición "aleatoria" simulada
        int espacios_izquierda = 10 + (rand() % 40);
        int espacios_arriba = 3 + (rand() % 8);

        for(int i = 0; i < espacios_arriba; i++) {
            printf("\n");
        }
        for(int i = 0; i < espacios_izquierda; i++) {
            printf(" ");
        }

        printf("╔═════════╗\n");
        for(int i = 0; i < espacios_izquierda; i++) {
            printf(" ");
        }
        printf("║    %c    ║\n", caracter_objetivo);
        for(int i = 0; i < espacios_izquierda; i++) {
            printf(" ");
        }
        printf("╚═════════╝\n");

        printf("\n\n¡ESCRIBE EL CARÁCTER! (Tienes 3 segundos)\n");

        double inicio = obtener_tiempo_actual_alta_precision();

        // Leer entrada del usuario de forma simple
        char tecla_presionada = '\0';
        int caracter_leido = 0;

        // Timer simple de 3 segundos
        double tiempo_transcurrido = 0;
        while(tiempo_transcurrido < 3.0) {
            // Intentar leer sin bloquear
            system("stty raw -echo");
            struct timeval tv = {0, 100000}; // 100ms timeout
            fd_set fds;
            FD_ZERO(&fds);
            FD_SET(0, &fds); // stdin es 0

            if(select(1, &fds, NULL, NULL, &tv) > 0) {
                tecla_presionada = getchar();
                caracter_leido = 1;
                break;
            }
            system("stty cooked echo");

            // Actualizar tiempo
            double tiempo_actual = obtener_tiempo_actual_alta_precision();
            tiempo_transcurrido = tiempo_actual - inicio;
        }
        system("stty cooked echo"); // Asegurar modo normal

        double fin = obtener_tiempo_actual_alta_precision();
        double tiempo_reaccion = (fin - inicio) * 1000;

        // Verificar resultado
        limpiar_pantalla();
        printf("Caza de Caracteres | Ronda %d/%d\n", ronda + 1, total_rondas);
        printf("=====================================\n");

        if(caracter_leido && tecla_presionada == caracter_objetivo && tiempo_reaccion <= 3000) {
            printf("✅ ¡ATRAPADO! Carácter: %c\n", caracter_objetivo);
            printf("   Tiempo: %.0f ms\n", tiempo_reaccion);
            aciertos++;
            tiempos[ronda] = tiempo_reaccion;
        } else if(tiempo_reaccion > 3000) {
            printf("❌ ¡SE ESCAPÓ! Carácter: %c\n", caracter_objetivo);
            printf("   Te demoraste demasiado (%.0f ms)\n", tiempo_reaccion);
            tiempos[ronda] = -1;
        } else if(caracter_leido && tecla_presionada != caracter_objetivo) {
            printf("❌ ERROR: Presionaste '%c', era '%c'\n",
                   tecla_presionada, caracter_objetivo);
            printf("   Tiempo: %.0f ms\n", tiempo_reaccion);
            tiempos[ronda] = -1;
        } else {
            printf("❌ NO RESPONDISTE: Era '%c'\n", caracter_objetivo);
            tiempos[ronda] = -1;
        }

        if(ronda < total_rondas - 1) {
            printf("\nPreparando siguiente carácter...\n");
            pausa_ms(2000);
        }
    }

    // Mostrar estadísticas
    mostrar_estadisticas_caza(tiempos, total_rondas, aciertos);
}


void mostrar_estadisticas_caza(double tiempos[], int total_rondas, int aciertos) {
    limpiar_pantalla();
    printf("=====================================\n");
    printf("       📊 ESTADÍSTICAS CAZA\n");
    printf("=====================================\n");

    double suma_tiempos = 0;
    double mejor_tiempo = 9999;
    int tiempos_validos = 0;

    printf("\nResultados por ronda:\n");
    for(int i = 0; i < total_rondas; i++) {
        printf("Ronda %d: ", i + 1);
        if(tiempos[i] > 0 && tiempos[i] <= 3000) {
            printf("%.0f ms ✅\n", tiempos[i]);
            suma_tiempos += tiempos[i];
            tiempos_validos++;
            if(tiempos[i] < mejor_tiempo) {
                mejor_tiempo = tiempos[i];
            }
        } else if(tiempos[i] > 3000) {
            printf("Tiempo agotado ❌\n");
        } else {
            printf("Error ❌\n");
        }
    }

    printf("\n--- RESUMEN ---\n");
    printf("Caracteres atrapados: %d/%d (%.1f%%)\n",
           aciertos, total_rondas,
           (aciertos * 100.0) / total_rondas);

    if(tiempos_validos > 0) {
        double promedio = suma_tiempos / tiempos_validos;
        printf("Tiempo promedio: %.0f ms\n", promedio);
        printf("Mejor tiempo: %.0f ms\n", mejor_tiempo);

        // Evaluación
        printf("\n🏆 EVALUACIÓN:\n");
        if(promedio < 1500 && aciertos == total_rondas)
            printf("¡Excelente! Ojos de águila 🦅\n");
        else if(promedio < 2000 && aciertos >= total_rondas - 1)
            printf("Muy bueno, coordinación perfecta 💪\n");
        else if(aciertos >= total_rondas - 2)
            printf("Bien, sigue practicando 📈\n");
        else
            printf("Sigue entrenando, mejorarás 🎯\n");
    }

    printf("\nPresiona ENTER para volver al menú...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
}
