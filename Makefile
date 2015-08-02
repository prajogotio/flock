CC=g++
CFLAGS=-W -Wall -Wextra -pedantic -std=c++0x 
CFRAMEWORK=-framework sfml-network -framework sfml-system -framework sfml-graphics -framework sfml-window
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

all: flock

flock: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(CFRAMEWORK)

%.o:%.cpp
	$(CC) $(CFLAGS) -o $@ -c $< $(CFRAMEWORK)

clean:
	rm -f flock $(OBJECTS)



