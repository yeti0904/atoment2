ifneq ($(filter $(PLATFORM), windows win64),)
CC   = x86_64-w64-mingw32-g++
else ifeq ($(PLATFORM), win32)
CC   = i686-w64-mingw32-g++
else
CC   = g++
endif
src  = $(wildcard src/*.cc)
args = -std=c++17 -Wall -Wextra -Werror -pedantic
ifneq ($(filter $(PLATFORM), windows win64 win32),)
args += -static -static-libgcc -static-libstdc++
endif
ifeq ($(OS),Windows_NT)
args += -static -static-libgcc -static-libstdc++
endif
out  = bin/atm

build:
	mkdir -p bin
	$(CC) $(src) $(args) -o $(out) -s

debug:
	mkdir -p bin
	$(CC) $(src) $(args) -o $(out) -g

release:
	mkdir -p bin
	$(CC) $(src) $(args) -o $(out) -O3

clean:
	rm -rf bin
