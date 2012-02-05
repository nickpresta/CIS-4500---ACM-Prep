CXX=g++
CPPFLAGS=--std=c++0x -Wall -Wextra -Werror -O3

SRCS=zoo.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: zoo

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) zoo

