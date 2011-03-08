UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
LDFLAGS = -lOpenCL -I/usr/include/nvidia-current
endif

ifeq ($(UNAME), Darwin)
LDFLAGS = -framework OpenCL
endif

main: main.c
	gcc -o main main.c $(LDFLAGS) -std=c99 -Wall

clean:
	rm -f main
