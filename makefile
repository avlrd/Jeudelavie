CC = gcc
CCG = gcc -g
CFLAGS = -Wall
IFLAGS = -I include

MODE = GUI

ifeq ($(MODE), GUI)
	SRC :=  main.c cairo.c jeu.c grille.c
	IFLAGS := $(IFLAGS) -I/usr/include/cairo
	LFLAGS = -lcairo -lm -lX11
else ifeq ($(MODE), TXT)
	SRC := main.c io.c jeu.c grille.c

else
$(error Erreur: Mode disponibles : GUI - TXT)
endif


BPATH = bin/
OPATH = obj/
DPATH = doc/
CPATH = src/
OBJECTS = $(SRC:.c=.o)
OBJECTS := $(addprefix $(OPATH), $(OBJECTS))

vpath %.c src

$(BPATH)main : $(OBJECTS)
	mkdir -p $(BPATH)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

$(OPATH)%.o : %.c
	mkdir -p $(OPATH)
	$(CCG) $(CFLAGS) -o $@ -c $< $(IFLAGS)

.PHONY : clean

clean :
	rm -rf $(BPATH) $(OPATH) $(DPATH)
	rmdir $(DPATH)
	@echo "\nClean\n"


dist:	
	tar -cJf VillardArthur-GoL-v0.1.tar.xz src/ include/ makefile Doxyfile
	@echo "\nArchive créée\n"

doc :
	doxygen Doxyfile
	@echo "\nDocumentation générée\n"