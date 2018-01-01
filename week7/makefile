CC = gcc

FLAGS = -c -g -Wall

SRCS = bfs.c

LIBS = -L../lib/implementation/

INCLUDES = -I../lib/include/

LFLAGS = -labs -lgraph -lfdr

OBJS = $(SRCS:.c=.o)

PROGRAM = main

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $(OBJS) $(INCLUDES) $(LIBS) $(LFLAGS)

.c.o: $(SRCS)
	$(CC) $(FLAGS) $(INCLUDES) $(SRCS)

clean:
	rm -rf core $(OBJS) *~ $(PROGRAM)
