# Compiler and flags
CC = clang++
CFLAGS = -std=c++11
SFML_INCLUDE = -I /opt/homebrew/Cellar/sfml/2.6.0/include
SFML_LIB = -L /opt/homebrew/Cellar/sfml/2.6.0/lib
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Source file and output executable
SRC = main.cpp
OUT = main

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SFML_INCLUDE) $(SFML_LIB) $(SFML_LIBS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)

.PHONY: all clean

