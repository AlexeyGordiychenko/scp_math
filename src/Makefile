CC=gcc
CFLAGS=-Wall -Werror -Wextra -g -fmax-errors=1
LDFLAGS=-L. -lcheck -ls21_math -lm -lsubunit

LIB_SRCS=s21_math.c s21_math.h
LIB_OBJS=$(LIB_SRCS:.c=.o)
LIB=libs21_math.a

all: test

test: unit_tests.c $(LIB)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ 

$(LIB): $(LIB_SRCS)
	ar rcs $(LIB) $(LIB_SRCS)

clean:
	rm -f $(LIB_OBJS) $(LIB) test

.PHONY: all clean
