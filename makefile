CXX = g++
CXXFLAGS = -std=c++11 -Wall -I.
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
VALGRIND = valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes

all: demo testcounter

demo: Demo.o tree.o
	$(CXX) Demo.o tree.o -o demo $(LDFLAGS)

testcounter: TestCounter.o tree.o
	$(CXX) TestCounter.o tree.o -o testcounter $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

check: demo
	$(VALGRIND) ./demo

clean:
	rm -f *.o demo testcounter
