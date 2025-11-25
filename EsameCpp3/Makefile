CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude
SRCS = main.cpp $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)
TARGET = caserma

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) *.o caserma.exe

run: $(TARGET)
	./$(TARGET)
