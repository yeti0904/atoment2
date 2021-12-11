CC   = g++
src  = $(wildcard src/*.cc)
args = -std=c++11 -Wall -Wextra -Werror -pedantic -s -o
out  = bin/atm

build:
	mkdir -p bin
	$(CC) $(src) $(args) $(out)

release:
	mkdir -p bin
	$(CC) $(src) $(args) $(out) -O3

clean:
	rm -rf bin