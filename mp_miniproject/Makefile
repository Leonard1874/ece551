SOURCES=commandshell.cpp
OBJS=$(patsubst %.cpp, %.o, $(SOURCES))
CPPFLAGS=-ggdb3 -Wall -Werror -pedantic -std=gnu++98

cmd: $(OBJS)
	g++ $(CPPFLAGS) -o cmd $(OBJS)
%.o: %.cpp commandshell.hpp
	g++ $(CPPFLAGS) -c $<

clean:
	rm test *~ *.o
