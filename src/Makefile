CC = g++
CFLAGS = -g -Wall
SRCS = detection.cpp
PROG = detection.bin

OPENCV = `pkg-config opencv --cflags --libs`
LIBS = $(OPENCV) 

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:

