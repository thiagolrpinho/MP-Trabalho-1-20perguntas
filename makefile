CC=g++
CFLAGS=-I.

testa_arvore: testa_arvore.cpp arvore.c
	$(CC) -o testa_arvore testa_arvore.cpp arvore.c $(CFLAGS)
