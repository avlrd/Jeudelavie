CC = gcc -g
CFLAGS = -W -Wall
IFLAGS = -I include
OPATH = obj/
CPATH = src/
OBJECTS = $(addprefix $(OPATH), main.o grille.o io.o jeu.o)

vpath %.c src

bin/main : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(OPATH) %.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(IFLAGS)

clean :
	rm -rf obj/* bin/*
	@echo "\nClean\n"


dist:	
	tar -Jcvf VillardArthur-GoL-v0.1.tar.xz $^
	@echo "\nArchive créée\n"

doc :
	doxygen Doxyfile