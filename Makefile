CXX = g++
CXXFLAGS = -std=c++17 -Wall -c
LXXFLAGS = -std=c++17 
OBJECTS = rubik.o main.o graph.o
TARGET = main

$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) $(OBJECTS) -o $(TARGET) 
rubik.o: rubik.cpp 
	$(CXX) $(CXXFLAGS) rubik.cpp -o rubik.o
graph.o: graph.cpp 
	$(CXX) $(CXXFLAGS) graph.cpp -o graph.o
main.o: main.cpp graph.h rubik.h
	$(CXX) $(CXXFLAGS) main.cpp -o main.o
clean:
	rm -fv $(TARGET) $(OBJECTS)
