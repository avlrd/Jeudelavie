CC = gcc
CCG = gcc -g
CFLAGS = -Wall
IFLAGS = -I include
LIBFLAGS = -lgj -L$(LPATH)
MODE = GUI

ifeq ($(MODE), GUI)
	SRC = main.c cairo.c
	IFLAGS := $(IFLAGS) -I/usr/include/cairo
	LFLAGS = -lcairo -lm -lX11
else ifeq ($(MODE), TXT)
	SRC = main.c io.c
	CFLAGS := -DMODE=TXT

else
$(error Erreur: Mode disponibles : GUI - TXT)

endif


BPATH = bin/
OPATH = obj/
DPATH = doc/
CPATH = src/
LPATH = lib/
MAINOBJ = $(SRC:.c=.o)
MAINOBJ := $(addprefix $(OPATH), $(MAINOBJ))
LIBOBJ = grille.o jeu.o
LIBOBJ := $(addprefix $(OPATH), $(LIBOBJ))

vpath %.c src

$(BPATH)main : $(MAINOBJ) $(LPATH)libgj.a
	mkdir -p $(BPATH)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS) $(LIBFLAGS)

$(LPATH)libgj.a : $(LIBOBJ)
	mkdir -p $(LPATH)
	ar -crv libgj.a $(LIBOBJ)
	ranlib libgj.a
	mv *.a $(LPATH)

$(OPATH)%.o : %.c
	mkdir -p $(OPATH)
	$(CCG) $(CFLAGS) -o $@ -c $< $(IFLAGS)

.PHONY : clean

clean :
	rm -rf $(BPATH) $(OPATH) $(DPATH) $(LPATH)
	@echo "\nClean\n"


dist:	
	tar -cJf VillardArthur-GoL-v1.0.tar.xz src/ include/ makefile Doxyfile
	@echo "\nArchive créée\n"

doc :
	doxygen Doxyfile
	@echo "\nDocumentation générée\n"