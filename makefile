CC = gcc
CCG = gcc -g
CFLAGS = -Wall
IFLAGS = -I include
OPATH = obj/
CPATH = src/
BPATH = bin/
DPATH = doc/
OBJECTS = $(addprefix $(OPATH), main.o grille.o io.o jeu.o)

vpath %.c src

$(BPATH)main : $(OBJECTS)
	mkdir -p $(BPATH)
	$(CC) $(CFLAGS) -o $@ $^

$(OPATH)%.o : %.c
	mkdir -p $(OPATH)
	$(CCG) $(CFLAGS) -o $@ -c $< $(IFLAGS)

clean :
	rm -rf $(BPATH) $(OPATH) $(DPATH)
	rmdir $(DPATH)
	@echo "\nClean\n"


dist:	
	tar -cJf VillardArthur-GoL-v0.1.tar.xz $^
	@echo "\nArchive créée\n"

doc :
	doxygen Doxyfile
	@echo "\nDocumentation générée\n"