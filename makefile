CXX=g++
CXXFLAGS=-std=c++17 -Wall -Iinclude -I/usr/include/SFML
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

all: main

main: src/main.cpp
	$(CXX) $(CXXFLAGS) src/main.cpp -o main $(LDFLAGS)

clean:
	rm -f main
all