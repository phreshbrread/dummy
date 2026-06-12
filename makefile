all: dummy

dummy:
	mkdir -p bin/ && gcc -Wall -Wextra src/main.c -o bin/dummy

clean:
	rm -r bin/
