all:
	gcc -g -Wall src/main.c -o snake -lncurses
clean:
	rm snake
