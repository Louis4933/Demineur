CC=gcc#on appellera la fonction gcc par CC
RM=rm -f#on supprimera les fichiers objets à l'aide de la commande rm -f en l'appellant RM
LMO=-lm -o#on compile a l'aide de la commande -lm -o qu'on appellera LMO
SRC=$(wildcard *.c)#on appellera par SRC les fichiers sources en .c
HEAD=$(wildcard *.h)#on appellera par HEAD les fichiers headers en .h
OBJ=$(SRC:.c=.o)#on remplace tous les fichiers .c dans src par des fichiers .o qu'on place dans bin
PROG=demineur#le nom de l'executable est demineur

all : $(PROG)

demineur : $(OBJ) #demineur depend des fichiers objets
	$(CC) $^ $(LMO) $@ 
#la commande est : gcc fichiersobjets.o -lm -o demineur
#$^ est la liste des dependances et $@ est la cible

OBJ : $(SRC) $(HEAD)
	$(CC) -c $(SRC) $(LMO) $@
#la commande est : gcc -c fichierssources.c fichiersentetes.h -lm -o fichiersobjets.o

#on ne confond pas le nom d'un fichier "clean" et la fonction clean
.PHONY : clean

#on utilise la commande make clean dans le terminal pour supprimer les fichiers objets
clean :
	$(RM) $(OBJ)