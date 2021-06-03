CXX ?= g++
CXXFLAGS += -std=c++17 -pthread -Wall -pedantic -Werror -Wextra -Wno-unused-variable -g
PROG ?= prog
OBJ := test.o SortBinFile.o HelpFunctions.o

all: $(PROG)

test: all
	./$(PROG)

$(PROG): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) $(LDFLAGS) -o $@

clean:
	rm -rf $(OBJ) $(PROG) *.txt

test.o: SortBinFile.h HelpFunctions.h

.PHONY: clean test all
