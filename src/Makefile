CC = gcc -Wall -Werror -Wextra
C++FLAGS = -std=c++17 -lstdc++
GTESTFLAGS = -pthread -lgtest
GCOVFLAGS = -fprofile-arcs -ftest-coverage

OS := $(shell uname)

ifeq ($(OS), Darwin)
    FLAGSYSTEM = 
else
    FLAGSYSTEM = -lrt -lm
endif

all: test

test:  
	$(CC) tests/*.cc $(C++FLAGS) $(GTESTFLAGS) -o s21_test $(FLAGSYSTEM)
	./s21_test

rebuild: clean all

clean: 
	rm -rf *.o s21_test s21_report *.a a.out *.gcno *.gcda s21_test.dSYM *.info report 3DViewer dist s21_matrix
