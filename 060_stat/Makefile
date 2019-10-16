CC = gcc
CFLAGS = -std=gnu99 -pedantic -Wall -o3
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))
mystat : $(OBJS)
	gcc -o $@ $(OBJS)
.PHONY: clean depend
clean:
	rm -f mystat *.c~ *.h~
depend:
	makedepend $(SRCS)

# DO NOT DELETE

test-power.o: /usr/include/stdio.h /usr/include/stdlib.h
power.o: /usr/include/stdio.h /usr/include/stdlib.h
