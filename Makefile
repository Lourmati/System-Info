CC=		gcc
CCFLAGS=	-std=c99 -g

PROGS=		exercice1 

all:
	make clean
	make $(PROGS)

clean:
	rm -f *.o 2> /dev/null
	rm -f $(PROGS) 2> /dev/null

exercice1:	info_systeme.c
	$(CC) -o info_systeme $(CCFLAGS)  info_systeme.c

