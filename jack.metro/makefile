CC=gcc

metronome: metro.o
	$(CC) -o $@ $^ `pkg-config --cflags --libs jack` 

metro.o: metro.c
	$(CC) -c -o $@ $^

clean:
	rm -f *.o metronome
