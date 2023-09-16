# Makefile

# Compiler and flags
CC = g++
CFLAGS = -std=c++20

# Target executable
BASE_GAME = base_tictactoe

# Source files
BASE_SRC = base_tictactoe.cpp base_tictactoe_board.cpp

all: $(BASE_GAME)

$(BASE_GAME): $(SRC)
	$(CC) $(CFLAGS) $(BASE_SRC) -o $(BASE_GAME)

clean:
	rm -f $(BASE_GAME)
