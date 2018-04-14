IDIR	=./include
CC      = g++ -std=c++11
CFLAGS  = -Wall -g -I$(IDIR)

ODIR	= ./src/obj
LDIR	=./lib
SDIR	=./src

LIBS	=-lm

_DEPS	= btree.hpp stringnode.hpp catch.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = tests_main.o tests_btree.o tests_game_engine.o btree.o game_engine.o stringnode.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC)	-c	-o 	$@	$<	$(CFLAGS)

all_tester: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
