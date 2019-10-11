CC = g++
CFLAGS = -std=gnu++98 -pedantic -Wall -o3
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRCS))
code : $(OBJS)
	g++ -o $@ $(OBJS)
.PHONY: clean depend
clean:
	rm -f code *.cpp~ *.h~
depend:
	makedepend $(SRCS)

# DO NOT DELETE

code.o: /usr/include/stdio.h /usr/include/stdlib.h
