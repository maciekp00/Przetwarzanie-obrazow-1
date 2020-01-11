IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR=../lib

LIBS=-lm

_DEPS = negatyw.h konturowanie.h progowanie.h rozciaganie.h rozmywanie_poziome.h wyswietl.h zmiana_poziomow.h zapisz.h
DEPS = $(pathsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=konturowanie.o negatyw.o progowanie.o rozciaganie.o rozmywanie_poziome.o wyswietl.o zmiana_poziomow.o zapisz.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ) 
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) 
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
