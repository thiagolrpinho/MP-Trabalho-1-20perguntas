IDIR	=./include
CC      = g++ -std=c++11
CFLAGS  = -I$(IDIR)

ODIR	= ./src/obj
LDIR	=./lib
SDIR	=./src

LIBS	=-lm

_DEPS	= btree.hpp catch.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = tests_btree.o btree.o tests_main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
		$(CC)	-c	-o 	$@	$<	$(CFLAGS)

BTree_tester: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
