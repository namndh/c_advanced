CC=gcc

FLAGS = -g -Wall

CFLAGS = -c $(FLAGS)

INCLUDES = -I../include/

LIBS = ../implementation/

LFLAGS= -lfdr -labs

SRCS = graph.c

OBJS = $(SRCS:.c=.o)

PROGRAM = libgraph.a

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	ar ru $(LIBS)libgraph.a $(OBJS)
	ranlib $(LIBS)libgraph.a

.c.o:
	$(CC) $(INCLUDES) $(CFLAGS) $(SRCS)

clean:
	rm -rf core  $(OBJS) $(PROGRAMS) *~
