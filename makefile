CC = gcc -g
CFLAGS = -W -Wall
SOURCES = $(wildcard *.c)
OBJETS = $(SOURCES:.c=.o)
EXEC = main

$(EXEC) : $(OBJETS)
	$(CC) $(FLAGS) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm $(EXEC) $(OBJETS)

doc:
	doxygen Doxyfile 

dist:	
	tar -Jcvf GoL_AV.tar.xz .*.c *.h makefile Doxyfile README.md
