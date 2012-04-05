CXX=clang
CPPFLAGS=--std=c++0x -Wall -Wextra -Werror -O3 -lstdc++

SRCS=granddinner.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: granddinner

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) granddinner

