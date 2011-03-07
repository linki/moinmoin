# from: http://dandesousa.com/2010/01/16/compiling-opengl-on-mac-os-x-or-linux/
# on linux do that before: sudo apt-get install freeglut3-dev
#
# -framework Carbon doesn't seem to be needed
#
# TODO: test on linux

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
LDFLAGS = -lGL -lglut -lGLU
endif

ifeq ($(UNAME), Darwin)
LDFLAGS = -framework OpenGL -framework GLUT -framework Carbon
endif

main: main.c
	gcc -o main main.c $(LDFLAGS) -std=c99 -Wall

clean:
	rm -f main
