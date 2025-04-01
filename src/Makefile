FLAGS = -Wall -Werror -Wextra -std=c++20 -ggdb -D_GLIBCXX_DEBUG
LIBS = -lgtest -lgtest_main -pthread
TEST_DIR = ./tests
SRCS = $(filter-out $(TEST_DIR)/%, $(wildcard /*.cpp *.cpp))
OBJS = $(patsubst %.cpp, %.o, $(SRCS))
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(patsubst %.cpp, %.o, $(TEST_SRCS))

all: clean s21_containers.a test

%.o: %.cpp
	g++ $(FLAGS) -c $< -o $@

s21_containers.a: $(OBJS)
	ar rcs $@ $(OBJS)

test: s21_containers.a $(TEST_OBJS)
	g++ $(FLAGS) -o test.out $(TEST_OBJS) s21_containers.a $(LIBS)
	./test.out

clean:
	rm -rf *.o */*.o *.a *.out