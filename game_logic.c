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

        double inicio = obtener_tiempo_actual();

        // Leer la tecla presionada (sin esperar Enter)
        // Versión simplificada para evitar problemas de portabilidad
        system("stty raw -echo");  // Modo raw para leer sin Enter
        char tecla_presionada = getchar();
        system("stty cooked echo"); // Volver al modo normal

        double fin = obtener_tiempo_actual();
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
