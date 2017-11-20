CC = g++
CFLAGS=`pkg-config --cflags opencv`
LIBS=`pkg-config --libs opencv`

all:bio

bio: src/Main.cpp
	$(CC) $(CFLAGS) $(LIBS) -o bin/Main src/Main.cpp

demo: bin/Main
	./bin/Main demo.png

clean:
	rm -f src/*.o
	rm -f bin/*