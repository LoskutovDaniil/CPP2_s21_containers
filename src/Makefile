VALGRINDFLAGS = --trace-children=yes --track-origins=yes --leak-check=full --show-leak-kinds=all

COMPILER = gcc

CPPFLAGS = -Werror -Wall -Wextra -g
CPPLIBS = -lstdc++ -lm

GTESTFLAGS = `pkg-config --cflags gtest` # -DGTEST_HAS_PTHREAD=1
GTESTLIBS = `pkg-config --libs gtest`    # -lgtest

TESTSFILES = tests/s21_*_tests/*.cpp test.cpp
HEADERFILE = s21_containers.h containers_source/*.h

OUT = s21_containers.out

test:
	$(COMPILER) $(GTESTFLAGS) $(CPPFLAGS) $(TESTSFILES) -o $(OUT) $(GTESTLIBS) $(CPPLIBS) 
	clear
	./s21_containers.out

leaks:
	$(COMPILER) $(GTESTFLAGS) $(CPPFLAGS) $(TESTSFILES) -o $(OUT) $(GTESTLIBS) $(CPPLIBS) 
	clear
	valgrind $(VALGRINDFLAGS) ./s21_containers.out

clang-format:
	clang-format -style=file:../materials/linters/.clang-format -n $(TESTSFILES) $(HEADERFILE)
clang-format_i:
	clang-format -style=file:../materials/linters/.clang-format -i $(TESTSFILES) $(HEADERFILE)