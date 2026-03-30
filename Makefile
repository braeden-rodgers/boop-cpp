# Compiler
CXX = g++
CXXFLAGS = -Wall -Werror -g

# Target executable name
TARGET = boop

# Object files
OBJS = main.o game.o boop.o

# Default rule
all: $(TARGET)

# Link step
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile each .cc file into an .o file
main.o: main.cc game.h boop.h
	$(CXX) $(CXXFLAGS) -c main.cc

game.o: game.cc game.h
	$(CXX) $(CXXFLAGS) -c game.cc

boop.o: boop.cc boop.h
	$(CXX) $(CXXFLAGS) -c boop.cc

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)