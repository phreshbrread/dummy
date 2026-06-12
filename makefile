all: dummy

dummy: ./src/main.c
	gcc -Wall -Wextra ./src/main.c -o dummy

clean:
	rm -f dummy
