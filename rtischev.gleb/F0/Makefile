CXX = g++
CXXFLAGS = -Wall -std=c++17
SRCS = main.cpp dict.cpp utils.cpp
TARGET = main.out

all: $(TARGET)
$(TARGET): $(SRCS) ; $(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)
run: $(TARGET) ; ./$(TARGET) < test_input.txt > test_output.txt
clean: ; rm -f $(TARGET) test_output.txt dict.txt
