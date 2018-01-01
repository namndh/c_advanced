CC=gcc

FLAGS = -g -Wall

CFLAGS = -c $(FLAGS)

INCLUDES = -I../../../lib/include

LIBS = -L../../../lib/implementation

LFLAGS= -lfdr -labs

SRCS = graph.c test.c

OBJS = $(SRCS:.c=.o)

PROGRAMS = test


all: $(PROGRAMS)

$(PROGRAMS): $(OBJS)
	$(CC) $(FLAG) $(INCLUDES) -o $(PROGRAMS) $(OBJS) $(LIBS) $(LFLAGS)

.c.o:
	$(CC) $(INCLUDES) $(CFLAGS) $(SRCS)

clean:
	rm -rf core  $(OBJS) $(PROGRAMS)
