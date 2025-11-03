# FastBrain - Makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=gnu99 -O2
TARGET = fastbrain
SOURCES = main.c game_logic.c utils.c
OBJECTS = $(SOURCES:.c=.o)

# Colores para output
GREEN = \033[0;32m
BLUE = \033[0;34m
NC = \033[0m # No Color

.PHONY: all clean install uninstall

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "$(BLUE)🔨 Compilando FastBrain...$(NC)"
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "$(GREEN)✅ FastBrain compilado exitosamente!$(NC)"
	@echo "$(BLUE)🎮 Ejecutar con: ./$(TARGET)$(NC)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(BLUE)🧹 Limpiando archivos compilados...$(NC)"
	rm -f $(TARGET) $(OBJECTS)
	@echo "$(GREEN)✅ Limpieza completada!$(NC)"

install: $(TARGET)
	@echo "$(BLUE)📦 Instalando FastBrain...$(NC)"
	cp $(TARGET) /usr/local/bin/
	@echo "$(GREEN)✅ FastBrain instalado en /usr/local/bin/$(NC)"
	@echo "$(BLUE)🎮 Ahora puedes ejecutar desde cualquier lugar con: fastbrain$(NC)"

uninstall:
	@echo "$(BLUE)🗑️ Desinstalando FastBrain...$(NC)"
	rm -f /usr/local/bin/$(TARGET)
	@echo "$(GREEN)✅ FastBrain desinstalado!$(NC)"

help:
	@echo "FastBrain - Opciones de compilación:"
	@echo "  make all     - Compila el proyecto (por defecto)"
	@echo "  make clean   - Limpia archivos compilados"
	@echo "  make install - Instala en /usr/local/bin/"
	@echo "  make uninstall - Desinstala el programa"
	@echo "  make help    - Muestra esta ayuda"
