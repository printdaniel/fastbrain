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


//----------------------------------------------------------------------------
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
    printf("\nPresiona ENTER para comenzar...");

    // Limpiar buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    int total_operaciones = 8;
    int puntuacion = 0;
    int aciertos = 0;
    double tiempos[total_operaciones];

    // Niveles de dificultad
    int nivel_actual = 1;
    int operaciones_por_nivel = 2;

    for(int op = 0; op < total_operaciones; op++) {
        // Avanzar nivel cada 2 operaciones
        if(op > 0 && op % operaciones_por_nivel == 0) {
            nivel_actual++;
        }

        limpiar_pantalla();
        printf("Cálculo Mental | Op %d/%d | Nivel %d\n", op + 1, total_operaciones, nivel_actual);
        printf("=====================================\n");

        // Generar operación según nivel
        int a, b, resultado_correcto;
        char operador;
        int tiempo_limite;

        generar_operacion(nivel_actual, &a, &b, &operador, &resultado_correcto, &tiempo_limite);

        // Mostrar operación
        printf("\n\n    ");
        if(operador == '+' || operador == '-' || operador == '*') {
            printf("%2d %c %2d = ?", a, operador, b);
        } else {
            printf("(%d %c %d) = ?", a, operador, b);
        }

        printf("\n\n    Tiempo límite: %d segundos\n", tiempo_limite);
        printf("\n    Tu respuesta: ");
        fflush(stdout);

        double inicio = obtener_tiempo_actual_alta_precision();

        // Leer respuesta del usuario
        int respuesta_usuario;
        int leido = 0;
        double tiempo_transcurrido = 0;

        while(tiempo_transcurrido < tiempo_limite) {
            // Intentar leer la respuesta
            if(scanf("%d", &respuesta_usuario) == 1) {
                leido = 1;
                break;
            }

            // Limpiar buffer si hay error
            while ((c = getchar()) != '\n' && c != EOF);

            // Actualizar tiempo
            double tiempo_actual = obtener_tiempo_actual_alta_precision();
            tiempo_transcurrido = tiempo_actual - inicio;
        }

        double fin = obtener_tiempo_actual_alta_precision();
        double tiempo_respuesta = (fin - inicio) * 1000;

        // Limpiar buffer
        while ((c = getchar()) != '\n' && c != EOF);

        // Verificar resultado
        limpiar_pantalla();
        printf("Cálculo Mental | Op %d/%d | Nivel %d\n", op + 1, total_operaciones, nivel_actual);
        printf("=====================================\n");

        if(leido && respuesta_usuario == resultado_correcto && tiempo_respuesta <= tiempo_limite * 1000) {
            printf("✅ ¡CORRECTO! %d %c %d = %d\n", a, operador, b, resultado_correcto);
            printf("   Tiempo: %.0f ms\n", tiempo_respuesta);

            // Calcular puntos (más puntos por mayor velocidad)
            int puntos_base = nivel_actual * 10;
            double factor_velocidad = 1.0 - (tiempo_respuesta / (tiempo_limite * 2000.0));
            int puntos_extra = (int)(puntos_base * factor_velocidad);
            int puntos_ronda = puntos_base + puntos_extra;

            printf("   Puntos: +%d (%d base + %d velocidad)\n", puntos_ronda, puntos_base, puntos_extra);

            puntuacion += puntos_ronda;
            aciertos++;
            tiempos[op] = tiempo_respuesta;
        } else if(tiempo_respuesta > tiempo_limite * 1000) {
            printf("❌ ¡TIEMPO AGOTADO! %d %c %d = %d\n", a, operador, b, resultado_correcto);
            tiempos[op] = -1;
        } else if(leido && respuesta_usuario != resultado_correcto) {
            printf("❌ ERROR: Dijiste %d, era %d\n", respuesta_usuario, resultado_correcto);
            printf("   %d %c %d = %d\n", a, operador, b, resultado_correcto);
            tiempos[op] = -1;
        } else {
            printf("❌ NO RESPONDISTE: %d %c %d = %d\n", a, operador, b, resultado_correcto);
            tiempos[op] = -1;
        }

        if(op < total_operaciones - 1) {
            printf("\nSiguiente operación en 2 segundos...\n");
            pausa_ms(2000);
        }
    }

    // Mostrar estadísticas
    mostrar_estadisticas_calculo(tiempos, total_operaciones, aciertos, puntuacion);
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
            // Asegurar que no dé negativo
            if(*a < *b) { int temp = *a; *a = *b; *b = temp; }
            *resultado = *a - *b;
            break;
        case '*': *resultado = *a * *b; break;
    }
}

void mostrar_estadisticas_calculo(double tiempos[], int total_ops, int aciertos, int puntuacion) {
    // AGREGAR ESTA LÍNEA AL INICIO DE LA FUNCIÓN:
    int c;

    limpiar_pantalla();
    printf("=====================================\n");
    printf("     📊 ESTADÍSTICAS CÁLCULO\n");
    printf("=====================================\n");

    double suma_tiempos = 0;
    double mejor_tiempo = 9999;
    int tiempos_validos = 0;

    printf("\nResultados por operación:\n");
    for(int i = 0; i < total_ops; i++) {
        printf("Op %d: ", i + 1);
        if(tiempos[i] > 0) {
            printf("%.0f ms ✅\n", tiempos[i]);
            suma_tiempos += tiempos[i];
            tiempos_validos++;
            if(tiempos[i] < mejor_tiempo) {
                mejor_tiempo = tiempos[i];
            }
        } else {
            printf("Error/Tiempo ❌\n");
        }
    }

    printf("\n--- RESUMEN ---\n");
    printf("Aciertos: %d/%d (%.1f%%)\n",
           aciertos, total_ops,
           (aciertos * 100.0) / total_ops);
    printf("Puntuación total: %d puntos\n", puntuacion);

    if(tiempos_validos > 0) {
        double promedio = suma_tiempos / tiempos_validos;
        printf("Tiempo promedio: %.0f ms\n", promedio);
        printf("Mejor tiempo: %.0f ms\n", mejor_tiempo);

        // Evaluación
        printf("\n🏆 EVALUACIÓN:\n");
        if(puntuacion >= 300)
            printf("¡GENIO MATEMÁTICO! 🧠\n");
        else if(puntuacion >= 200)
            printf("Excelente cálculo mental 💪\n");
        else if(puntuacion >= 100)
            printf("Buen trabajo, sigue practicando 📈\n");
        else
            printf("Sigue entrenando, mejorarás 🎯\n");

        printf("\n💡 Tip: Practica diariamente para mejorar tu velocidad\n");
    }

    printf("\nPresiona ENTER para volver al menú...");
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
}


