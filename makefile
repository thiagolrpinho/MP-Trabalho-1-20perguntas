CC=g++
CFLAGS=-I.
DEPS = arvore.h

%.o: %.c  $(DEPS)
		$(CC) -c  -o  $@  $<  $(CFLAGS)

testa_arvore: testa_arvore.cpp arvore.c
	$(CC) -o testa_arvore testa_arvore.cpp arvore.c $(CFLAGS)
