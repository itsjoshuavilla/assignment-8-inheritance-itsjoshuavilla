# Makefile for Lab 7 extension 

CXX       := g++
CXXFLAGS  := -std=c++17 -O2 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wundef -DM_PI=3.14159265358979323846
LDFLAGS   := 
LDLIBS    := -lm

SRC       := lab8_fields.cpp
TARGET    := lab8_fields

.PHONY: all run clean debug

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Debug build with sanitizers
debug: CXXFLAGS += -g -O0 -fsanitize=address,undefined
debug: LDFLAGS  += -fsanitize=address,undefined
debug: clean $(TARGET)

# Clean build artifacts
clean:
	$(RM) $(TARGET)
