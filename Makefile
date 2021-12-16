ifeq ($(PLATFORM), windows)
CC   = x86_64-w64-mingw32-g++
else
CC   = g++
endif
src  = $(wildcard src/*.cc)
args = -std=c++17 -Wall -Wextra -Werror -pedantic -o
ifeq ($(PLATFORM), windows)
out  = bin/atm.exe
else
out  = bin/atm
endif

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
