CC=gcc

LIBS=`pkg-config --cflags --libs jack`

metronome: metro.o
	$(CC) -o $@ $^ $(LIBS)

metro.o: metro.c
	$(CC) -c -o $@ $^

clean:
	rm -f *.o metronome
