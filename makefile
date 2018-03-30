IDIR	=./include
CC      = g++ -std=c++11
CFLAGS  = -I$(IDIR)

ODIR	= ./src/obj
LDIR	=./lib
SDIR	=./src

LIBS	=-lm

_DEPS	= arvore.h catch.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = testa_arvore.o arvore.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
		$(CC)	-c	-o 	$@	$<	$(CFLAGS)

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
		$(CC)	-c	-o 	$@	$<	$(CFLAGS)

testa_arvore: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
