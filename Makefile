CC=gcc


all: tp2
tp2: utils.o
utils.o: tp2.c utils.h utils.h

clean:
		rm -f tp2 utils.o
run: tp2
		./tp2