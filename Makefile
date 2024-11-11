main: $(wildcard *.c)
	gcc $(wildcard *.c) -o main -F/Library/Frameworks -framework SDL2 -std=c17 -Wl,-rpath,/Library/Frameworks