NAME = parser
SRCS = main.cpp parser.cpp
OBJS = $(SRCS:.cpp=.o)
CC = g++ -std=c++17
HEADERS = parser.hpp

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

$(OBJS): %.o : %.cpp $(HEADERS)
	$(CC) -c $< -o $@

clean:
	rm -rf $(OBJS) $(NAME)

re: clean all

test: re
	./$(NAME)

.PHONY: all, re, clean, test
