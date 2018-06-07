IDIR	=./include
CC      = g++ -std=c++11
CFLAGS  = -Wall -g -I$(IDIR) --coverage 
GCOVFLAGS = $(CFLAGS) --coverage -fPIC  -O0 

ODIR	= ./src/obj
LDIR	=./lib
SDIR	=./src
TDIR	=./tests

LIBS	=-lm

_DEPS	= game_interface.hpp game_engine.hpp btree.hpp stringnode.hpp catch.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_TOBJ = game_interface.o game_engine.o btree.o stringnode.o tests_main.o tests_btree.o 
TOBJ = $(patsubst %,$(ODIR)/%,$(_TOBJ))

_OBJ = game_interface.o game_engine.o btree.o stringnode.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC)	-c	-o 	$@	$<	$(CFLAGS)

$(ODIR)/%.o: $(TDIR)/%.cpp $(DEPS)
	$(CC)	-c	-o 	$@	$<	$(CFLAGS) 

play_game: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


btree_tester:$(TOBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

gcov_btree: $(TOBJ)
	$(CC) $(GCOVFLAGS) -o $@ $^ $(LIBS)

_TOBJ += tests_game_statement.o 
TOBJ = $(patsubst %,$(ODIR)/%,$(_TOBJ))

game_statement_tester:$(TOBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

gcov_statement: $(TOBJ)
	$(CC) -o $@ $^ $(GCOVFLAGS) $(LIBS)

_TOBJ += tests_game_engine.o 
TOBJ = $(patsubst %,$(ODIR)/%,$(_TOBJ))

game_engine_tester:$(TOBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

gcov_engine: $(TOBJ)
	$(CC) -o $@ $^ $(GCOVFLAGS) $(LIBS)

_TOBJ += tests_game_interface.o 
TOBJ = $(patsubst %,$(ODIR)/%,$(_TOBJ))

game_interface_tester:$(TOBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

all_tester: $(TOBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

gcov_tester: $(TOBJ)
	$(CC) -o $@ $^ $(GCOVFLAGS) $(LIBS)

gcovr_html:
	gcovr -r . --html --html-details -o ./tests/gcov/tests-detailts.html
	
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
