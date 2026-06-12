all: dummy

dummy: src/main.c
	mkdir -p bin/ && gcc -Wall -Wextra src/main.c -o bin/dummy

clean:
	rm -rf bin/
