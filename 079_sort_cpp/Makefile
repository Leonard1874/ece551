CC = g++
CFLAGS=-ggdb3 -std=gnu++98 -pedantic -Wall
SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp,%.o,$(SRCS))
sortLines:$(OBJS)
	g++ -o $@ $(OBJS)
.PHONY:clean depend
clean:
	rm -r *.o *.cpp~ *.h~
depend:
	makedepend $(SRCS)
# DO NOT DELETE
