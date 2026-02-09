#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game_logic.h"
#include "utils.h"

int main() {
    // Inicializar generador de números aleatorios
    srand(time(NULL));

    int opcion;

    printf("=====================================\n");
    printf("          🧠 FASTBRAIN 🧠\n");
    printf("    Entrena tu mente - Mejora tu vida\n");
    printf("=====================================\n");

    do {
        printf("\n--- MENÚ PRINCIPAL ---\n");
        printf("1. 🎯 Reflejos - Mano Derecha\n");
        printf("2. ⚡ Reflejos - Caza de Caracteres\n");
        printf("3. 🧮 Cálculo Mental\n");
        printf("4. 🔢 Memoria de Números\n");
        printf("5. 🎨 Stroop Test (NUEVO)\n");
        printf("6. 🚪 Salir\n");
        printf("\nElige una opción (1-6): ");

        if(scanf("%d", &opcion) != 1) {
            // Limpiar buffer si hay error de entrada
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            opcion = 0;
        }

        switch(opcion) {
            case 1:
                ejercicio_reflejos_mano_derecha();
                break;
            case 2:
                ejercicio_caza_caracteres();
                break;
            case 3:
                ejercicio_calculo_mental();
                break;
            case 4:
                ejercicio_memoria_numeros();
                break;
            case 5:
                ejercicio_stroop_test();
                break;
            case 6:
                printf("¡Hasta la próxima! Sigue entrenando 🧠\n");
                break;
            default:
                printf("❌ Opción no válida. Intenta de nuevo.\n");
                break;
        }

    } while(opcion != 6);

    return 0;
}
