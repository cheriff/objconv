all: objconv

CFLAGS=-Wall -Werror -O2

SRC=$(wildcard *.cpp)
OBJ=$(patsubst %.cpp,%.o,$(SRC))

main.o: obj.h timer.h
obj.o: obj.h

$(OBJ): Makefile

$(OBJ): %.o : %.cpp
	clang++ $(CFLAGS) -ggdb  -c $< -o $@ --std=c++11

objconv: $(OBJ)
	clang++ $(CFLAGS) -ggdb  $^ -o $@

run: objconv
	./objconv gt86.obja

clean:
	rm -f objconf $(OBJ)
