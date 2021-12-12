CC   = g++
src  = $(wildcard src/*.cc)
args = -Wall -Wextra -Werror -pedantic -o
out  = bin/atm

build:
	mkdir -p bin
	$(CC) $(src) $(args) $(out) -s

debug:
	mkdir -p bin
	$(CC) $(src) $(args) $(out) -g

release:
	mkdir -p bin
	$(CC) $(src) $(args) $(out) -O3

clean:
	rm -rf bin
