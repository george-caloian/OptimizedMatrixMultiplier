build: tema2.c utils.c utils.h
	g++ -Wall -o tema2 utils.c tema2.c -O1 -funroll-loops -static-libstdc++
run: build
	./tema2 tema2.cfg
verbose: tema2.c utils.c utils.h
	g++ -D VERBOSE -Wall -o tema2 utils.c tema2.c

clean:
	-rm -rf tema2 a.out
