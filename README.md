# 🧠 FastBrain

**Entrena tu cerebro con ejercicios de cálculo, reflejos y memoria**

## 🎯 Objetivo
FastBrain es un programa en C diseñado para mejorar:
- Velocidad de reacción
- Cálculo mental
- Memoria a corto plazo
- Reflejos y coordinación

## 🚀 Características
- [ ] Ejercicios de reflejos por mano
- [ ] Cálculos aritméticos con timer
- [ ] Entrenamiento de memoria visual
- [ ] Seguimiento de progreso
- [ ] Múltiples niveles de dificultad

## 🛠️ Compilación
```bash
gcc main.c game_logic.c utils.c -o fastbrain
# 🧠 FastBrain - Entrenamiento Cerebral en C

![FastBrain Banner](https://img.shields.io/badge/FastBrain-Entrenamiento_Cerebral-blue)
![C Language](https://img.shields.io/badge/Lenguaje-C-orange)
![License](https://img.shields.io/badge/Licencia-MIT-green)

**FastBrain** es una aplicación de entrenamiento cerebral desarrollada en C que desafía y mejora tus habilidades cognitivas a través de ejercicios interactivos y medibles.

## 🎯 Características

### 🏋️‍♂️ 4 Ejercicios de Entrenamiento Cerebral

1. **🎯 Reflejos - Mano Derecha**
   - Entrena la coordinación y velocidad de reacción
   - Teclas QWERTY específicas para mano derecha
   - Medición precisa en milisegundos
   - Estadísticas de tiempo y precisión

2. **⚡ Caza de Caracteres**
   - Mejora la coordinación ojo-mano
   - Caracteres en posiciones aleatorias
   - Timer de desaparición (3 segundos)
   - Evaluación de velocidad y precisión

3. **🧮 Cálculo Mental**
   - Desarrolla agilidad numérica
   - 4 niveles de dificultad progresiva
   - Operaciones: suma, resta, multiplicación
   - Sistema de puntuación con bonus por velocidad

4. **🔢 Memoria de Números**
   - Fortalece la memoria a corto plazo
   - Secuencias progresivas (4-7 dígitos)
   - Tiempo adaptativo para memorizar
   - Tips personalizados para mejorar

## 🚀 Instalación y Compilación

### Requisitos
- Compilador GCC
- Sistema Linux/Unix o Windows con compatibilidad
- Terminal que soporte caracteres Unicode

### Compilación
```bash
# Clonar el repositorio
git clone https://github.com/printdaniel/fastbrain.git
cd fastbrain

# Compilar el proyecto
make

# O compilar manualmente
gcc -std=gnu99 -o fastbrain main.c game_logic.c utils.c
