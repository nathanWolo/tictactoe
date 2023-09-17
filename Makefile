# Makefile

# Compiler and flags
CC = g++
CFLAGS = -std=c++20 -fsanitize=undefined -fsanitize=address

# Target executable
BASE_GAME = base_tictactoe

# Source files
BASE_SRC = base_tictactoe.cpp base_tictactoe_board.cpp

ULTIMATE_GAME = ultimate_tictactoe

ULTIMATE_SRC = ultimate_tictactoe.cpp ultimate_tictactoe_board.cpp base_tictactoe_board.cpp utt_engine.cpp
all: $(BASE_GAME) $(ULTIMATE_GAME)

$(BASE_GAME): $(BASE_SRC)
	$(CC) $(CFLAGS) $(BASE_SRC) -o $(BASE_GAME) 

$(ULTIMATE_GAME): $(ULTIMATE_SRC)
	$(CC) $(CFLAGS) $(ULTIMATE_SRC) -o $(ULTIMATE_GAME)

clean:
	rm -f $(BASE_GAME) $(ULTIMATE_GAME)
