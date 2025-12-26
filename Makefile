all: build

build:
	gcc -o build/exec/cave src/cave.c -Wall -Wextra -pedantic -std=c11

clean:
	rm -f build/exec/cave

run: build
	./build/exec/cave -i tests/test1.cav

.PHONY: all build clean