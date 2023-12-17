# Author : Gineste Jarod
# Compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall
LDFLAGS =

# Nom des l'exécutables
EXECUTABLE_S = scrutin
EXECUTABLE_T = tests

# Obtenez tous les fichiers source dans le répertoire courant
SOURCES = $(wildcard *.c)

# Liste des fichiers objets générés à partir des sources
OBJECTS_S = $(filter-out tests.o, $(SOURCES:.c=.o))
OBJECTS_T = $(filter-out scrutin.o, $(SOURCES:.c=.o))

all: $(EXECUTABLE_S) $(EXECUTABLE_T) cleanobj

$(EXECUTABLE_S): $(OBJECTS_S)
	@$(CC) -o $@ $^ $(LDFLAGS)
	

$(EXECUTABLE_T): $(OBJECTS_T)
	@$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(OBJECTS_S) $(OBJECTS_T) $(EXECUTABLE_S) $(EXECUTABLE_T)

# remove les .o apres avoir fais un make all
cleanobj:
	rm -f $(OBJECTS_S) $(OBJECTS_T)

deliver: $(SOURCES) $(EXECUTABLE_S) $(EXECUTABLE_T)
	@zip deliver.zip $(SOURCES) $(EXECUTABLE_S) $(EXECUTABLE_T)

.PHONY: all clean deliver
