# Compilateur
CC = gcc

# Options de compilation
CFLAGS = -Werror -Wall -pedantic -Wextra
LDFLAGS =

# Nom de l'exécutable (spécifiez ici le nom de l'exécutable souhaité)
EXECUTABLE = verify_my_vote

# Obtenez tous les fichiers source dans le répertoire courant
SOURCES = $(wildcard *.c)

# Liste des fichiers objets générés à partir des sources
OBJECTS = $(SOURCES:.c=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

.PHONY: all clean
