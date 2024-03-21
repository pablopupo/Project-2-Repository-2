# Define the compiler to use
CXX = g++

# Define any compile-time flags
CXXFLAGS = -std=c++11 -Wall

# Define the target executable name
TARGET = project2.out

# Define any directories containing header files
INCLUDES = -I.

# Define source files to compile
# This uses a wildcard to compile all .cpp files in the current directory
SRCS = $(wildcard *.cpp)

# Define object files based on source files (replace .cpp with .o)
OBJS = $(SRCS:.cpp=.o)

# First rule - default rule to build the project
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS)

# Rule to clean out compiled objects and the executable
clean:
	rm -f $(OBJS) $(TARGET)

# Define the rule for compiling object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# A rule that does nothing to prevent problems with intermediate files
.PRECIOUS: %.o
