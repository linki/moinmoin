# from: http://dandesousa.com/2010/01/16/compiling-opengl-on-mac-os-x-or-linux/
# on linux do that before: sudo apt-get install freeglut3-dev
#
# http://www.transmissionzero.co.uk/computing/using-glut-with-mingw/
# glut32.dll is needed
#
# TODO: test on linux, mac

CC = gcc
CFLAGS= -Wall
SOURCE = main.c
EXECUTABLE = main

UNAME = $(shell uname)

ifeq ($(UNAME), Linux)
LDFLAGS = -lGL -lglut -lGLU
endif

ifeq ($(UNAME), Darwin)
LDFLAGS = -framework OpenGL -framework GLUT
endif

ifeq ($(findstring MINGW32, $(UNAME)), MINGW32)
LDFLAGS = -lglu32 -lglut32 -lopengl32 -Wl,--subsystem,windows
EXECUTABLE = main.exe
endif
	
$(EXECUTABLE): $(SOURCE) 
	$(CC) $(SOURCE) -o $(EXECUTABLE) $(LDFLAGS) $(CFLAGS)

clean:
	$(RM) $(EXECUTABLE)

