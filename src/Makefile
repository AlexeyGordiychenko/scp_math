# This makefile will provide this folder structure after compiling:
# .
# ├── obj
# │   └── scp_math.o
# ├── gcov
# │   ├── gcov_report.css
# │   ├── gcov_report.html
# │   └── gcov_report.scp_math.c.[hash].html
# │   └── obj
# │       ├── scp_math.gcda
# │       ├── scp_math.gcno
# │       └── scp_math.o
# ├── scp_math.a
# ├── scp_math.c
# ├── scp_math.h
# ├── test.c
# ├── test.h
# ├── test
# ├── Makefile
#
# All the object files for the lib go to the obj folder
# All the object files for the ./test (including *.gcno, *.gcda) go to the gcov/obj folder
# The gcov report with additional files (*.css and details html) go to the gcov folder

CC=gcc
CFLAGS=-Wall -Werror -Wextra -g
LDFLAGS=-lcheck -pthread -lgcov -lm -lrt
ifeq ($(shell uname), Linux)
	LDFLAGS+=-lsubunit
endif

GCOVFLAGS=--coverage

OBJS_DIR=obj

GCOV_REPORT=gcov_report
GCOV_DIR=gcov
GCOV_OBJ_DIR=$(GCOV_DIR)/$(OBJS_DIR)

LIB_SRCS=scp_math.c
LIB_OBJS=$(patsubst %.c,$(OBJS_DIR)/%.o,$(LIB_SRCS))
LIB_OBJS_GCOV=$(patsubst %.c,$(GCOV_OBJ_DIR)/%.o,$(LIB_SRCS))
LIB=scp_math.a

TEST=test
TEST_SRCS=test.c

all: $(LIB)

$(TEST): $(TEST_SRCS) $(LIB_OBJS_GCOV)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(LIB): $(LIB_OBJS)
	ar rcs $(LIB) $^

$(OBJS_DIR)/%.o: %.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(GCOV_OBJ_DIR)/%.o: %.c
	mkdir -p $(GCOV_OBJ_DIR)
	$(CC) $(CFLAGS) $(GCOVFLAGS) -c $< -o $@

$(GCOV_REPORT): $(TEST)
	mkdir -p $(GCOV_DIR)
#	> /dev/null 2>&1 to suppress all the stdout and stderr messages
#	|| true to continue even if tests have failed cases
	./test > /dev/null 2>&1 || true
	gcovr --html --html-details -o $(GCOV_DIR)/$(GCOV_REPORT).html --filter $(LIB_SRCS)

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./$(TEST)

clean:
	rm -rf $(OBJS_DIR)/* $(LIB) $(TEST) $(GCOV_DIR)/*

rebuild: clean all

.PHONY: all clean rebuild $(GCOV_REPORT) valgrind
