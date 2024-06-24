CXX = g++
CXXFLAGS = -std=c++11 -Wall -I. # Include directory flags here
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system # Linker flags for SFML

# Source files
SOURCES = Demo.cpp TestCounter.cpp tree.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = demo

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXECUTABLE)
