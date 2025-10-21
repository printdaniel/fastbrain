# Compilador
CC = gcc
# Opciones de compilación
CFLAGS = -Wall -Wextra -std=c99 -O2
# Bibliotecas
LIBS =

# Archivos fuente
SRCS = main.c game_logic.c utils.c
# Archivos objeto
OBJS = $(SRCS:.c=.o)
# Nombre del ejecutable
TARGET = fastbrain

# Regla principal
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

# Reglas para archivos objeto
main.o: main.c game_logic.h utils.h
	$(CC) $(CFLAGS) -c main.c

game_logic.o: game_logic.c game_logic.h utils.h
	$(CC) $(CFLAGS) -c game_logic.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

# Limpiar archivos compilados
clean:
	rm -f $(OBJS) $(TARGET)

# Instalar (copiar a /usr/local/bin)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

.PHONY: all clean install
