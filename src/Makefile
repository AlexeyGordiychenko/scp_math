# This makefile will provide this folder structure after compiling:
# .
# ├── obj
# │   ├── s21_math.gcda
# │   ├── s21_math.gcno
# │   └── s21_math.o
# ├── gcov
# │   ├── gcov_report.css
# │   ├── gcov_report.html
# │   └── gcov_report.s21_math.c.[hash].html
# ├── libs21_math.a
# ├── s21_math.c
# ├── s21_math.h
# ├── test.c
# ├── test
# ├── Makefile
#
# All the object files (including *.gcno, *.gcda) go to the obj folder
# The gcov report with additional files (*.css and details html) go to the gcov folder

CC=gcc
CFLAGS=-Wall -Werror -Wextra -g -fmax-errors=1
LDFLAGS=-L. -lcheck -ls21_math
ifeq ($(shell uname), Linux)
	LDFLAGS += -lsubunit -lgcov -lm
endif
GCOVFLAGS=--coverage

OBJS_DIR=obj

LIB_SRCS=s21_math.c
LIB_OBJS=$(patsubst %.c,$(OBJS_DIR)/%.o,$(LIB_SRCS))
LIB=libs21_math.a

TEST=test
TEST_SRCS=test.c

GCOV_REPORT=gcov_report.html
GCOV_DIR=gcov

all: $(TEST)

$(TEST): $(TEST_SRCS) $(LIB)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ 

$(LIB): $(LIB_OBJS)
	ar rcs $(LIB) -o $^

$(OBJS_DIR)/%.o: %.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(GCOVFLAGS) -c $< -o $@

gcov_report: $(TEST)
	mkdir -p $(GCOV_DIR)
#	> /dev/null 2>&1 to suppress all the stdout and stderr messages
#	|| true to continue even if tests have failed cases
	./test > /dev/null 2>&1 || true
	gcovr --html --html-details -o $(GCOV_DIR)/$(GCOV_REPORT)

clean:
	rm -rf $(OBJS_DIR)/* $(LIB) $(TEST) $(GCOV_DIR)/*

rebuild: clean all

.PHONY: all clean rebuild gcov_report
