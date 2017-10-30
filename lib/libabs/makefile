CC = gcc
CFLAGS = -Wall -Werror -c

LIB_FOLDER = ../implementation/

SRCS = *.c

OBJS = $(SRCS:.c=.o)


all: libabs.a

libabs.a: $(OBJS)
	ar ru $(LIB_FOLDER)libabs.a $(OBJS)
	ranlib $(LIB_FOLDER)libabs.a

clean:
	rm -f core $(LIB_FOLDER)libabs.a *.o

.c.o:
	$(CC) $(CFLAGS) -c $(SRCS)

