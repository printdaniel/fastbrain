# 🏗️ Diario de Arquitectura - FastBrain

> **Propósito de este documento**: Documentar las decisiones arquitectónicas, técnicas y de diseño tomadas durante el desarrollo de FastBrain. Este diario me ayuda a entender mis propias decisiones, aprender de ellas, y comunicar el razonamiento detrás del código.

---

## 📋 Tabla de Contenidos

1. [Visión General del Proyecto](#visión-general-del-proyecto)
2. [Decisiones de Arquitectura](#decisiones-de-arquitectura)
3. [Decisiones de Gestión de Memoria](#decisiones-de-gestión-de-memoria)
4. [Estructura de Datos](#estructura-de-datos)
5. [Patrones y Convenciones](#patrones-y-convenciones)
6. [Aprendizajes y Reflexiones](#aprendizajes-y-reflexiones)
7. [Próximas Mejoras](#próximas-mejoras)

---

## 🎯 Visión General del Proyecto

### ¿Qué es FastBrain?
FastBrain es una aplicación de entrenamiento cognitivo desarrollada en C puro que permite entrenar diferentes habilidades mentales a través de ejercicios interactivos.

### Objetivos del Proyecto
1. **Técnico**: Aprender y practicar programación en C de nivel intermedio-avanzado
2. **Funcional**: Crear una herramienta útil para entrenar habilidades cognitivas
3. **Personal**: Mejorar mis propias capacidades cognitivas mediante el uso regular

### Scope Actual
- ✅ 4 ejercicios cognitivos implementados
- ✅ Sistema de estadísticas y retroalimentación
- ✅ Gestión de memoria dinámica
- ✅ Interfaz de línea de comandos interactiva
- ⏳ Sistema de guardado de progreso (pendiente)
- ⏳ Gráficos de evolución (pendiente)

---

## 🏛️ Decisiones de Arquitectura

### DECISIÓN 1: Separación en Módulos

**FECHA**: Inicio del proyecto (estructura base)

**CONTEXTO**:
Necesitaba organizar el código de forma que sea mantenible y escalable. Al principio consideré poner todo en un solo archivo, pero rápidamente vi que sería difícil de mantener.

**DECISIÓN**:
Separar el código en tres módulos principales:
```
main.c          - Punto de entrada y menú principal
game_logic.c    - Lógica de los ejercicios
utils.c         - Funciones utilitarias (pantalla, tiempo, pausas)
```

**ALTERNATIVAS CONSIDERADAS**:
1. ❌ Todo en un solo archivo `main.c`
   - Descartado: No escala, difícil de navegar
2. ❌ Un archivo por ejercicio (`reflejos.c`, `calculo.c`, etc.)
   - Descartado: Demasiada fragmentación para proyecto pequeño
3. ✅ **Tres módulos (main, game_logic, utils)**
   - Elegido: Balance entre organización y simplicidad

**RAZONES**:
- **Separación de responsabilidades**: Cada módulo tiene un propósito claro
- **Reusabilidad**: Las funciones de `utils.c` se pueden usar en todos los ejercicios
- **Mantenibilidad**: Es fácil encontrar dónde está cada cosa
- **Escalabilidad**: Puedo agregar ejercicios sin tocar `main.c` ni `utils.c`

**TRADE-OFFS**:
- ✅ Ganancia: Código organizado, fácil de navegar
- ⚠️ Sacrificio: Más archivos que compilar (pero el Makefile lo maneja)

**RESULTADO** (agregado después):
Funcionó muy bien. Cuando refactoricé a memoria dinámica, solo tuve que modificar `game_logic.c` y `game_logic.h`, sin tocar `main.c` ni `utils.c`. ¡La separación valió la pena!

---

### DECISIÓN 2: Uso de Makefile

**FECHA**: Inicio del proyecto

**CONTEXTO**:
Tener múltiples archivos `.c` significaba que compilar manualmente sería tedioso:
```bash
gcc main.c game_logic.c utils.c -o fastbrain  # Cada vez...
```

**DECISIÓN**:
Crear un `Makefile` con targets para compilar, limpiar e instalar.

**ALTERNATIVAS CONSIDERADAS**:
1. ❌ Compilar manualmente cada vez
2. ❌ Script bash simple
3. ✅ **Makefile profesional**

**RAZONES**:
- **Eficiencia**: Solo recompila lo que cambió (archivos `.o`)
- **Profesionalismo**: Es el estándar en proyectos C
- **Aprendizaje**: Quería aprender Make correctamente
- **Features**: Targets como `clean`, `install`, `help`

**CONTENIDO CLAVE DEL MAKEFILE**:
```makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=gnu99 -O2
TARGET = fastbrain
SOURCES = main.c game_logic.c utils.c
OBJECTS = $(SOURCES:.c=.o)
```

**TRADE-OFFS**:
- ✅ Ganancia: Compilación incremental, targets útiles, profesional
- ⚠️ Sacrificio: Curva de aprendizaje inicial de Make

**RESULTADO**:
Excelente decisión. El Makefile me ahorra tiempo y hace que el proyecto se vea más profesional.

---

### DECISIÓN 3: Portabilidad (Linux/Windows)

**FECHA**: Inicio del proyecto

**CONTEXTO**:
Quería que el código funcione tanto en Linux (mi sistema principal) como en Windows (por si lo comparto).

**DECISIÓN**:
Usar directivas de preprocesador para código específico de plataforma:

```c
#ifdef _WIN32
    #include <windows.h>
    system("cls");  // Windows
#else
    #include <unistd.h>
    system("clear");  // Linux
#endif
```

**ALTERNATIVAS CONSIDERADAS**:
1. ❌ Solo Linux
2. ❌ Usar librería externa para portabilidad
3. ✅ **Directivas de preprocesador (`#ifdef`)**

**RAZONES**:
- Sin dependencias externas
- Control total sobre el comportamiento
- Aprender el patrón correcto de portabilidad en C

**FUNCIONES PORTABLES IMPLEMENTADAS**:
- `limpiar_pantalla()` - cls/clear
- `pausa_ms()` - Sleep/nanosleep
- `obtener_tiempo_actual_alta_precision()` - clock/gettimeofday

**TRADE-OFFS**:
- ✅ Ganancia: Funciona en múltiples plataformas
- ⚠️ Sacrificio: Código un poco más complejo con `#ifdef`

**RESULTADO**:
Funciona bien. No he probado en Windows aún, pero el código está preparado.

---

## 💾 Decisiones de Gestión de Memoria

### DECISIÓN 4: Refactorización a Memoria Dinámica

**FECHA**: [Fecha de la refactorización - Febrero 2026]

**CONTEXTO**:
La versión inicial usaba arrays estáticos con tamaños fijos:
```c
int intentos = 7;  // Siempre 7, hardcodeado
double tiempos[intentos];
```

Esto funcionaba pero era inflexible. No podía cambiar el número de intentos sin recompilar.

**DECISIÓN**:
Refactorizar TODOS los ejercicios para usar memoria dinámica con `malloc()` y `free()`.

**ALTERNATIVAS CONSIDERADAS**:
1. ❌ Dejar arrays estáticos
   - Descartado: Inflexible, no escalable
2. ❌ Arrays estáticos grandes (ej: `double tiempos[100]`)
   - Descartado: Desperdicia memoria, no es profesional
3. ✅ **Memoria dinámica con malloc/free**
   - Elegido: Flexible, profesional, escalable

**RAZONES**:
- **Flexibilidad**: El usuario puede elegir cuántas rondas quiere
- **Aprendizaje**: Practicar gestión de memoria (tema clave en C)
- **Eficiencia**: Solo uso la memoria que necesito
- **Profesionalismo**: Así se hace en software real

**IMPLEMENTACIÓN**:
Creé estructuras para cada ejercicio y funciones de gestión:
```c
// Ejemplo: Reflejos
typedef struct {
    int total_intentos;
    int aciertos;
    double *tiempos;              // Array dinámico
    char *teclas_correctas;       // Array dinámico
    char *teclas_presionadas;     // Array dinámico
} DatosReflejos;

DatosReflejos* crear_datos_reflejos(int num_intentos);
void liberar_datos_reflejos(DatosReflejos *datos);
```

**PATRÓN APLICADO**:
1. Validar entrada
2. Reservar memoria para estructura principal
3. Reservar memoria para arrays dinámicos
4. Si falla malloc, liberar lo ya reservado y retornar NULL
5. Inicializar todos los valores
6. Retornar puntero a estructura

**TRADE-OFFS**:
- ✅ Ganancia: Flexibilidad total, memoria eficiente, código profesional
- ⚠️ Sacrificio: Más complejo, debo recordar liberar memoria

**RESULTADO**:
¡Funcionó perfectamente! El código es mucho más flexible y aprendí muchísimo sobre malloc/free.

**LECCIONES APRENDIDAS**:
- Siempre verificar que `malloc()` no retorne NULL
- Liberar memoria en orden inverso a como se reservó
- Usar estructuras para agrupar datos relacionados
- Evitar memory leaks liberando SIEMPRE

---

### DECISIÓN 5: Manejo de Errores en Malloc

**FECHA**: Durante la refactorización

**CONTEXTO**:
`malloc()` puede fallar (retornar NULL) si no hay memoria disponible. Debo manejar este caso.

**DECISIÓN**:
Implementar manejo de errores en cascada:
```c
DatosReflejos *datos = malloc(sizeof(DatosReflejos));
if (datos == NULL) {
    fprintf(stderr, "Error: malloc falló\n");
    return NULL;
}

datos->tiempos = malloc(n * sizeof(double));
if (datos->tiempos == NULL) {
    free(datos);  // ⚠️ Liberar lo ya reservado
    return NULL;
}

datos->teclas_correctas = malloc(n * sizeof(char));
if (datos->teclas_correctas == NULL) {
    free(datos->tiempos);  // ⚠️ Liberar en orden
    free(datos);
    return NULL;
}
```

**ALTERNATIVAS CONSIDERADAS**:
1. ❌ Ignorar posible fallo de malloc
   - Descartado: Causaría segfaults
2. ❌ Solo verificar la estructura principal
   - Descartado: Arrays podrían ser NULL y causar problemas
3. ✅ **Verificar cada malloc y liberar en cascada**

**RAZONES**:
- **Seguridad**: Previene segmentation faults
- **Robustez**: El programa no crashea si falta memoria
- **Profesionalismo**: Así se hace en código de producción

**TRADE-OFFS**:
- ✅ Ganancia: Código robusto, no crashea
- ⚠️ Sacrificio: Más líneas de código, más complejo

**RESULTADO**:
El código es mucho más robusto. Si falta memoria, el programa informa el error en lugar de crashear.

---

## 📊 Estructura de Datos

### DECISIÓN 6: Diseño de Estructuras por Ejercicio

**FECHA**: Durante la refactorización

**CONTEXTO**:
Antes pasaba múltiples parámetros a las funciones:
```c
mostrar_estadisticas_reflejos(tiempos, intentos, aciertos);  // 3 parámetros
```

**DECISIÓN**:
Crear estructuras específicas que agrupan todos los datos de cada ejercicio.

**DISEÑO DE ESTRUCTURAS**:

#### DatosReflejos
```c
typedef struct {
    int total_intentos;        // Cuántos intentos en total
    int aciertos;              // Cuántos acertó
    double *tiempos;           // Tiempos de reacción (ms)
    char *teclas_correctas;    // Qué tecla debía presionar
    char *teclas_presionadas;  // Qué tecla presionó realmente
} DatosReflejos;
```
**Razón de cada campo**:
- `total_intentos`: Necesito saber el tamaño de los arrays
- `aciertos`: Para calcular porcentaje
- `tiempos`: Para estadísticas (promedio, mejor tiempo)
- `teclas_correctas/presionadas`: Para mostrar detalle de errores

#### DatosCazaCaracteres
```c
typedef struct {
    int total_rondas;
    int aciertos;
    double *tiempos;
    char *caracteres_objetivo;
    char *caracteres_presionados;
} DatosCazaCaracteres;
```
**Similar a DatosReflejos** - Patrón consistente

#### DatosCalculo
```c
typedef struct {
    int total_operaciones;
    int aciertos;
    int puntuacion;           // Puntos acumulados
    double *tiempos;
} DatosCalculo;
```
**Campo único**: `puntuacion` - Este ejercicio tiene sistema de puntos

#### DatosMemoria
```c
typedef struct {
    int total_rondas;
    int aciertos;
    int longitud_maxima;      // Secuencia más larga alcanzada
    int *secuencia_correcta;  // Números a memorizar
    int *secuencia_usuario;   // Números que ingresó
    int capacidad_secuencia;  // Tamaño máximo del array
} DatosMemoria;
```
**Campos únicos**:
- `longitud_maxima`: Para estadísticas de progreso
- `capacidad_secuencia`: Necesito saber el tamaño máximo

**RAZONES PARA USAR ESTRUCTURAS**:
- **Encapsulación**: Todos los datos relacionados juntos
- **Menos parámetros**: Paso 1 puntero en lugar de 5-6 valores
- **Extensibilidad**: Fácil agregar campos nuevos
- **Claridad**: Nombres de campos auto-documentan el propósito

**TRADE-OFFS**:
- ✅ Ganancia: Código más limpio, fácil de extender
- ⚠️ Sacrificio: Debo definir y mantener las estructuras

**RESULTADO**:
Excelente decisión. Las funciones ahora son mucho más limpias:
```c
// Antes
mostrar_estadisticas_reflejos(tiempos, intentos, aciertos);

// Después
mostrar_estadisticas_reflejos(datos);  // ¡Mucho más limpio!
```

---

## 🎨 Patrones y Convenciones

### DECISIÓN 7: Patrón de Creación/Destrucción

**FECHA**: Durante la refactorización

**CONTEXTO**:
Con memoria dinámica, necesitaba un patrón consistente para crear y destruir estructuras.

**DECISIÓN**:
Implementar el patrón **Constructor/Destructor** para cada tipo de datos:

```c
// Constructor
TipoDatos* crear_datos_tipo(parametros);

// Destructor
void liberar_datos_tipo(TipoDatos *datos);
```

**CONVENCIONES ADOPTADAS**:

#### Nombres de Funciones
- `crear_datos_*()` - Reserva memoria e inicializa
- `liberar_datos_*()` - Libera toda la memoria

#### Estructura del Constructor
```c
TipoDatos* crear_datos_tipo(int param) {
    // 1. Validar parámetros
    if (param <= 0 || param > MAX) {
        fprintf(stderr, "Error: parámetro inválido\n");
        return NULL;
    }

    // 2. Reservar estructura principal
    TipoDatos *datos = malloc(sizeof(TipoDatos));
    if (datos == NULL) {
        fprintf(stderr, "Error: malloc falló\n");
        return NULL;
    }

    // 3. Inicializar campos básicos
    datos->campo1 = valor_inicial;

    // 4. Reservar arrays dinámicos (con error handling)
    datos->array = malloc(param * sizeof(tipo));
    if (datos->array == NULL) {
        free(datos);  // Limpiar antes de retornar
        return NULL;
    }

    // 5. Inicializar arrays
    for (int i = 0; i < param; i++) {
        datos->array[i] = valor_default;
    }

    return datos;
}
```

#### Estructura del Destructor
```c
void liberar_datos_tipo(TipoDatos *datos) {
    // 1. Verificar NULL (defensivo)
    if (datos == NULL) return;

    // 2. Liberar arrays (en orden inverso a creación)
    if (datos->array2 != NULL) free(datos->array2);
    if (datos->array1 != NULL) free(datos->array1);

    // 3. Liberar estructura principal
    free(datos);
}
```

**RAZONES**:
- **Consistencia**: Mismo patrón en todos los ejercicios
- **Seguridad**: Siempre verifico NULL
- **Mantenibilidad**: Fácil de entender y modificar
- **Profesional**: Patrón usado en software real (ej: GTK+, SDL)

**TRADE-OFFS**:
- ✅ Ganancia: Código predecible, fácil de mantener
- ⚠️ Sacrificio: Código más verboso

---

### DECISIÓN 8: Convenciones de Nomenclatura

**FECHA**: Inicio del proyecto

**DECISIÓN**:
Adoptar convenciones claras de nombres:

```c
// Tipos de datos (PascalCase)
typedef struct { ... } DatosReflejos;

// Funciones (snake_case)
void ejercicio_reflejos_mano_derecha();
DatosReflejos* crear_datos_reflejos(int n);

// Variables (snake_case)
int total_intentos;
double tiempo_reaccion;

// Constantes (UPPER_SNAKE_CASE)
const char TECLAS_MANO_DERECHA[] = "yuiophjklñnm,.-";
const int NUM_TECLAS = 15;
```

**RAZONES**:
- **Claridad**: Los nombres describen su propósito
- **Estándar C**: Sigue convenciones comunes en C
- **Legibilidad**: Fácil distinguir tipos, funciones, variables

---

## 🧠 Aprendizajes y Reflexiones

### Aprendizaje 1: Gestión de Memoria es Crítica

**Qué aprendí**:
Gestionar memoria manualmente es **difícil pero fundamental** en C. A diferencia de lenguajes con garbage collection, en C tengo control total pero también toda la responsabilidad.

**Errores que cometí (y corregí)**:
1. ❌ Al principio olvidaba verificar si malloc retornaba NULL
2. ❌ A veces liberaba memoria en el orden incorrecto
3. ❌ Olvidaba liberar memoria en algunos paths de error

**Cómo los corregí**:
- ✅ Ahora SIEMPRE verifico malloc
- ✅ Libero en orden inverso a la creación
- ✅ Uso un patrón consistente de error handling

**Herramientas que ayudan**:
- `valgrind --leak-check=full` - Detecta memory leaks
- Compilar con `-g` - Mejor debugging
- Compilar con `-Wall -Wextra` - Más warnings

---

### Aprendizaje 2: Estructuras Organizan Mejor que Múltiples Parámetros

**Antes**:
```c
void mostrar_estadisticas(double *tiempos, int total, int aciertos,
                          char *teclas_ok, char *teclas_user);
```
5 parámetros = confuso, propenso a errores

**Después**:
```c
void mostrar_estadisticas(DatosReflejos *datos);
```
1 parámetro = claro, difícil equivocarse

**Lección**: Cuando una función necesita muchos parámetros relacionados, probablemente debería ser una estructura.

---

### Aprendizaje 3: Separación de Responsabilidades Facilita Refactorización

**Reflexión**:
Cuando refactoricé a memoria dinámica, solo tuve que modificar:
- ✅ `game_logic.c` - Implementación
- ✅ `game_logic.h` - Declaraciones
- ❌ NO toqué `main.c` ni `utils.c`

Esto fue posible porque separé bien las responsabilidades desde el inicio.

**Lección**: La separación en módulos no es solo para organización, también facilita mantenimiento.

---

### Aprendizaje 4: Documentar Decisiones Mientras Codifico

**Reflexión**:
Al principio no documentaba por qué tomaba decisiones. Luego, al revisar código de semanas atrás, no recordaba por qué hice algo de cierta forma.

**Lección**: Este diario de arquitectura es invaluable. No solo para compartir, sino para mi yo futuro.

---

## 🔮 Próximas Mejoras

### Mejora 1: Sistema de Guardado de Progreso

**ESTADO**: ⏳ Pendiente

**DESCRIPCIÓN**:
Guardar estadísticas históricas en archivos para ver progreso a lo largo del tiempo.

**DECISIONES A TOMAR**:
- ¿Formato de archivo? (JSON, binario, CSV, texto plano)
- ¿Estructura de datos? (una entrada por sesión, agregado semanal, etc.)
- ¿Ubicación de archivos? (`~/.fastbrain/`, carpeta local, etc.)

**COMPLEJIDAD**: Media
**PRIORIDAD**: Alta (es la feature más pedida)

---

### Mejora 2: Refactorización de Código Duplicado

**ESTADO**: ⏳ Pendiente

**DESCRIPCIÓN**:
Hay código repetido en varios ejercicios que podría abstraerse:
- Countdown antes de mostrar estímulo
- Lectura de input con timeout
- Mostrar resultados de ronda

**DECISIÓN A TOMAR**:
¿Crear funciones auxiliares genéricas o dejar código específico para cada ejercicio?

**TRADE-OFF**:
- Menos duplicación vs. menos flexibilidad específica

**COMPLEJIDAD**: Baja
**PRIORIDAD**: Media

---

### Mejora 3: Tests Unitarios

**ESTADO**: ⏳ Pendiente

**DESCRIPCIÓN**:
Agregar tests para funciones de gestión de memoria y lógica de juegos.

**FRAMEWORK A CONSIDERAR**:
- CUnit
- Check
- Unity (para embedded)
- Escribir tests simples con assert()

**COMPLEJIDAD**: Media-Alta
**PRIORIDAD**: Media (buena práctica, pero no urgente)

---

## 📝 Template para Nuevas Decisiones

Cuando tome una nueva decisión importante, usaré este template:

```markdown
### DECISIÓN X: [Mejora en implementación de memoria]

**FECHA**: [3/01/2026]

**CONTEXTO**:
[Performance, sobre todo ante las mediciones de tiempo de reacción]

**DECISIÓN**:
[Qué decidí hacer]

**ALTERNATIVAS CONSIDERADAS**:
1. ❌ [Quitar ejercicios] - Descartado porque los ejercicios deben estar
3. ✅ **[Alternativa elegida]** - Mejorar el uso de la memoria

**RAZONES**:
- [Razón 1]
- [Razón 2]
- [Razón 3]

**TRADE-OFFS**:
- ✅ Ganancia: [Velocidad en la ejecución]
- ⚠️ Sacrificio: [Qué sacrifiqué o complejidad agregada]

**RESULTADO** (agregar después):
[Cómo resultó la decisión en la práctica]

[Qué aprendí de esta decisión]
```

---

## 🎯 Conclusión

Este diario documenta el viaje de FastBrain desde una idea simple hasta un proyecto bien estructurado con gestión profesional de memoria.

**Logros principales**:
- ✅ Arquitectura modular clara
- ✅ Gestión de memoria dinámica profesional
- ✅ Código portable (Linux/Windows)
- ✅ Patrón consistente en todos los ejercicios
- ✅ Manejo robusto de errores

**Próximos pasos**:
1. Sistema de guardado de progreso
2. Refactorización de código duplicado
3. Tests unitarios
4. Gráficos de evolución

---

**Última actualización**: [04/01/2026]
**Versión del proyecto**: 0.2.0 (post-refactorización memoria dinámica)
