CXX=g++
CPPFLAGS=--std=c++0x -Wall -Wextra -Werror -O3

SRCS=crypt.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: crypt

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) crypt

