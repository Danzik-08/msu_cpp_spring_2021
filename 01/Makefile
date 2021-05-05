NAME = allocator
SRCS = Allocator.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)
CC = g++ -std=c++17
HEADERS = Allocator.hpp

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

$(OBJS): %.o : %.cpp $(HEADERS)
	$(CC) -c $< -o $@

clean:
	rm -rf $(OBJS) $(NAME)

re: clean all

.PHONY: all, re, clean
