# Compiler to use
CXX = g++

# Compiler flags
# -Wall enables all warnings
# -std=c++11 ensures we use the C++11 standard
CXXFLAGS = -Wall -std=c++11

# The name of the executable to be created
TARGET = main

# Source files
# List all .cpp files that need to be compiled
SRCS = main.cpp Graph.cpp Node.cpp Edge.cpp

# Object files
# These are the .o files created after compilation
OBJS = $(SRCS:.cpp=.o)

# Default target that gets called when running 'make'
# It will compile the program and link the object files into an executable
all: $(TARGET)

# Rule to build the final executable
# $@ refers to the target (in this case, the final executable $(TARGET))
# $^ refers to all the dependencies (in this case, the object files $(OBJS))
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile the .cpp files into .o object files
# $< refers to the first dependency (in this case, a .cpp file)
# The -c flag compiles without linking
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean up all generated files
# It removes the object files and the final executable
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets are not actual files; this avoids issues if files with these names exist
.PHONY: all clean
