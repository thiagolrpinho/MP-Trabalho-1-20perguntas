IDIR	=./include
CC      = g++ -std=c++11
CFLAGS  = -Wall -g -I$(IDIR)

ODIR	= ./src/obj
LDIR	=./lib
SDIR	=./src
TDIR	=./tests

LIBS	=-lm

_DEPS	= game_interface.hpp game_engine.hpp btree.hpp stringnode.hpp catch.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_TOBJ = game_interface.o game_engine.o btree.o stringnode.o tests_main.o tests_btree.o tests_game_statement.o tests_game_engine.o tests_game_interface.o 
TOBJ = $(patsubst %,$(ODIR)/%,$(_TOBJ))

_OBJ = game_interface.o game_engine.o btree.o stringnode.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC)	-c	-o 	$@	$<	$(CFLAGS)

$(ODIR)/%.o: $(TDIR)/%.cpp $(DEPS)
	$(CC)	-c	-o 	$@	$<	$(CFLAGS)

all_tester: $(TOBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
