all: build
build:
\tgcc -o build/exec/cave src/cave.c -Wall -Wextra -pedantic -std=c11
clean:
\trm -f cave
run: build
\t./build/exec/cave -i tests/test1.cav
.PHONY: all build clean