CC = gcc
CFLAGS = -std=gnu99 -pedantic -Wall -o3
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))
breaker : $(OBJS)
	gcc -o $@ $(OBJS)
.PHONY: clean depend
clean:
	rm -f myProgram *.c~ *.h~
depend:
	makedepend $(SRCS)

# DO NOT DELETE

breaker.o: /usr/include/ctype.h /usr/include/features.h
breaker.o: /usr/include/stdc-predef.h /usr/include/endian.h
breaker.o: /usr/include/stdio.h /usr/include/stdlib.h /usr/include/alloca.h
