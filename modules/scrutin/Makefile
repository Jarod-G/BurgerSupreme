# Compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall
LDFLAGS =

# Nom de l'exécutable (spécifiez ici le nom de l'exécutable souhaité)
EXECUTABLE_S = scrutin
EXECUTABLE_T = tests

# Obtenez tous les fichiers source dans le répertoire courant
SOURCES = $(wildcard *.c)

# Liste des fichiers objets générés à partir des sources
OBJECTS_S = $(filter-out tests.o, $(SOURCES:.c=.o))
OBJECTS_T = $(filter-out scrutin.o, $(SOURCES:.c=.o))

all: $(EXECUTABLE)

$(EXECUTABLE_S): $(OBJECTS_S)
	@$(CC) -o $@ $^ $(LDFLAGS)

$(EXECUTABLE_T): $(OBJECTS_T)
	@$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(OBJECTS_S) $(OBJECTS_T)

.PHONY: all clean
