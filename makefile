CC      = g++
CFLAGS  = -I.
DEPS    = arvore.h
OBJ     = testa_arvore.o arvore.o

%.o: %.c  $(DEPS)
	$(CC) -c  -o  $@  $<  $(CFLAGS)

testa_arvore: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
