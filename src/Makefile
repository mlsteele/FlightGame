CC=clang++
CFLAGS=-c -Wall -I/usr/include
# -std=c++11 -stdlib=libc++
LDFLAGS=-lsfml-system -lsfml-window -lsfml-graphics -lglut -lGLU -lGL
SOURCES=Arena.cpp FlightGame.cpp InputHandler.cpp main.cpp Octree.cpp Oggler.cpp Orb.cpp Orientable.cpp Pushable.cpp Render.cpp Ship.cpp Strand.cpp
SRC_DIR=src
BUILD_DIR=build
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=FlightGame

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BUILD_DIR)/$@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
