# Define the C++ compiler to use
CXX = g++

# Define any directories containing header files
INCLUDES = 

# Define C++ compile flags
CXXFLAGS = -Wall -std=c++17 -O3 $(INCLUDES)

# Define the C++ source files
SRCS = dpll.cpp test.cpp

# Define the C++ object files 
OBJS = $(SRCS:.cpp=.o)

# Defines the executable file
MAIN = main

.PHONY: clean

all:    $(MAIN)

run: $(MAIN)
	./$(MAIN)

$(MAIN): $(OBJS) 
	$(CXX) $(CXXFLAGS) -o $(MAIN) $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)
