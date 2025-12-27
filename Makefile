all: build

build:
	gcc -o build/out/cave src/cave.c src/tokens.c src/lexer.c -Wall -Wextra -pedantic -std=c11

clean:
	rm -f build/out/cave

run: 
	./build/out/cave -i tests/test1.cav

.PHONY: all build clean