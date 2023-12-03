# Compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall

# Si FILE est défini, utilisez-le comme nom de fichier source
ifdef FILE
    SOURCES = $(FILE) 
else
    SOURCES = main.c  # Fichier source par défaut si FILE n'est pas défini
endif

# Nom de l'exécutable
EXECUTABLE = $(basename $(SOURCES))

# Liste des fichiers objets générés à partir des sources
OBJECTS = $(SOURCES:.c=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

.PHONY: all clean
