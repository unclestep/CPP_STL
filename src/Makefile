FLAGS = -Wall -Werror -Wextra -std=c++20 -ggdb -D_GLIBCXX_DEBUG
LIBS = -lgtest -lgtest_main -pthread
TEST_DIR = tests
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(patsubst %.cpp, %.o, $(TEST_SRCS))

all: clean test

%.o: %.cpp
	g++ $(FLAGS) -c $< -o $@

test: $(TEST_OBJS)
	g++ $(FLAGS) -o test.out $(TEST_OBJS) $(LIBS)
	./test.out

valgrind: 
	valgrind ./test.out

clean:
	rm -rf *.o */*.o *.out