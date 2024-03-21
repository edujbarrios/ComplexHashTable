CXX = g++
CXXFLAGS = -std=c++17 

SRCDIR = src
SOURCES = $(SRCDIR)/main.cpp
EXECUTABLE = hash

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f $(EXECUTABLE)
