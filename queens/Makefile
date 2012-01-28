CXX=g++
CPPFLAGS=--std=c++0x -Wall -Wextra -Werror -O3

SRCS=queens.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: queens

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) queens

