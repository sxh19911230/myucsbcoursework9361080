CC = g++
CFLAGS = -c -g -Wall
LDFLAGS = 
SOURCES = Record.cpp grading2.cpp
DEPS = Record.h
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = grading2
 
$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
 
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) $<

