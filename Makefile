# Makefile

# Compiler and flags
CC = g++
CFLAGS = -std=c++20

# Target executable
TARGET = base_tictactoe

# Source files
SRC = base_tictactoe.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
