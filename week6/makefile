CC = gcc

FLAGS = -c -g -Wall

SRCS = test.c

OBJS = $(SRCS:.c=.o)

LIBS = -L../lib/implementation/

INCLUDES = -I../lib/include/

LFLAGS = -labs -lgraph -lfdr

PROGRAM = test

all:	$(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $(OBJS) $(INCLUDES) $(LIBS) $(LFLAGS)

.c.o:	$(SRCS)
	$(CC) $(FLAGS) $(SRCS) $(INCLUDES)

clean:
	rm -rf core $(OBJS) $(PROGRAM) *~
