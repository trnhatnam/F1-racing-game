CC=g++
CCFLAGS= -Wall -Werror -std=c++17 -g
SRC= $(wildcard ../*.cpp)
OBJ= $(SRC:.cpp=.o)
TST= $(wildcard *.cpp)
OBJ_TEST = $(filter-out ../main.o, $(OBJ)) $(TST:.cpp=.o)

testcase.out : $(OBJ_TEST) 
	$(CC) $(CCFLAGS)  -o $@ $^ -lsfml-graphics -lsfml-window -lsfml-system; ./testcase.out

%.o: %.cpp
	$(CC) $(CCFLAGS) -I../ -o $@ -c $<

clean :
	rm -f testcase.out $(OBJ_TEST) 