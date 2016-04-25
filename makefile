# Compiler options
CC = g++
OPTCFLAGS= -Ofast -march=native 
CFLAGS= -Wall -Werror -std=c++11 $(OPTCFLAGS)
LDFLAGS= -static-libstdc++

# Directory organisation
BASEDIR = .
SRC = $(BASEDIR)/src
BUILD = $(BASEDIR)/build
BIN = $(BASEDIR)/bin

# Program name
TARGET = dna_to_bin

# Objects names
OBJECTS = $(BUILD)/dna_to_bin.o

# Rules

all: init $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(BIN)/$(TARGET) $^ 

$(BUILD)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf $(BUILD)/*.o
	rm -rf $(BIN)/$(TARGET)

init: 
	mkdir -p $(BUILD) $(BIN)

rebuild: clean $(TARGET)
