CC=clang++
CFLAGS=-Wall -std=c++11 -stdlib=libc++
# CREQS=-framework Foundation -framework SFML -lsfml-system -lsfml-window -framework GLUT -framework OpenGL
CREQS=-framework Foundation -framework SFML -framework sfml-system -framework sfml-window -framework GLUT -framework OpenGL
SRCROOT=src
BUILDROOT=build
TARGET=$(BUILDROOT)/FlightGame

all: FlightGame

r:
	$(TARGET)

d:
	gdb $(TARGET)

cr: FlightGame r


cd: FlightGame d

FlightGame:
	$(CC) $(CFLAGS) $(CREQS) $(SRCROOT)/*.cpp -o $(TARGET)
