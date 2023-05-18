CC=gcc
CFLAGS=-Wall -Werror -Wextra -g -fmax-errors=1
LDFLAGS=-L. -lcheck -ls21_math -lm -lsubunit

LIB_SRCS=s21_math.c
LIB_OBJS=$(LIB_SRCS:.c=.o)
LIB=libs21_math.a

TEST=test
TEST_SRCS=test.c

all: $(TEST)

$(TEST): $(TEST_SRCS) $(LIB)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ 

$(LIB): $(LIB_OBJS)
	ar rcs $(LIB) $(LIB_OBJS)

clean:
	rm -f $(LIB_OBJS) $(LIB) $(TEST)

.PHONY: all clean
