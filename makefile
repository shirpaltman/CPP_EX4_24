CXX = g++
CXXFLAGS = -std=c++11 -Wall -I.
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all: demo testcounter

demo: Demo.o tree.o
	$(CXX) Demo.o tree.o -o demo $(LDFLAGS)

testcounter: TestCounter.o tree.o
	$(CXX) TestCounter.o tree.o -o testcounter $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o demo testcounter
