CXX = g++
CXXFLAGS = -std=c++11 -Wall -Werror

TEST_EXEC = testWordCount

SRC = WordCount.cpp tddFuncs.cpp Lab07Test.cpp

OBJ = $(SRC:.cpp=.o)

.PHONY: all clean

all: $(TEST_EXEC)


$(TEST_EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<


test: $(TEST_EXEC)
	./$(TEST_EXEC)


clean:
	rm -f $(TEST_EXEC) *.o