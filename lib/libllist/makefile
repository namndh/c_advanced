CC = gcc

FLAGS = -Wall  -c -g

INCLUDE = -I../include/

LIB_FOLDER = ../implementation/

SRCS = $(wildcard *.c)

OBJS = $(SRCS:.c=.o)

PROGRAM = libllist.a

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	ar ru $(LIB_FOLDER)$(PROGRAM) $(OBJS)
	ranlib $(LIB_FOLDER)$(PROGRAM)

clean:
	rm -rf core $(LIB_FOLDER)$(PROGRAM) $(OBJS) *~

.c.o:
	$(CC) $(FLAGS) $(INCLUDE) $(LFLAGS) $(SRCS) 
