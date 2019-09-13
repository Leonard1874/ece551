CC = gcc
CFLAGS = -std=gnu99 -pedantic -Wall -o3
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))
test : $(OBJS)
	gcc -o $@ $(OBJS)
.PHONY: clean depend
clean:
	rm -f myProgram *.c~ *.h~
depend:
	makedepend $(SRCS)

# DO NOT DELETE

test.o: /usr/include/stdio.h /usr/include/stdlib.h /usr/include/string.h
