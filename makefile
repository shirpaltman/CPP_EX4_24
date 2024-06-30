CXX = clang++
CXXFLAGS = -std=c++11 -Werror -Wsign-conversion
VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all --error-exitcode=99
# SFML Libraries
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Sources and objects
DEMO_SOURCES = tree.cpp node.cpp Demo.cpp TreeVisualizer.cpp
TEST_SOURCES = tree.cpp node.cpp test.cpp TestCounter.cpp

DEMO_OBJECTS = $(DEMO_SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

# Targets
all: demo test

demo: $(DEMO_OBJECTS)
	$(CXX) $(DEMO_OBJECTS) -o demo $(SFML_LIBS)

test: $(TEST_OBJECTS)
	$(CXX) $^ -o test $(SFML_LIBS)

tidy:
	clang-tidy $(DEMO_SOURCES) $(TEST_SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: demo
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f *.o demo test gui
