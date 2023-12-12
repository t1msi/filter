CC=gcc
CFLAGS=-I.

all: filter gensig
filter:
	$(CC) $(CFLAGS) MedianFilter.c example.c -o MedianFilter

gensig:
	$(CC) $(CFLAGS) gensig.c -o gensig

clean:
	rm -rf *.o MedianFilter gensig
