all: objconv

CFLAGS=-Wall -Werror -O3 -ggdb

SRC=$(wildcard *.cpp)
OBJ=$(patsubst %.cpp,%.o,$(SRC))

-include Makefile.deps
Makefile.deps: $(SRC)
	$(CC) $(CFLAGS) -MM $(SRC) > Makefile.deps

$(OBJ): Makefile

$(OBJ): %.o : %.cpp
	clang++ $(CFLAGS) -ggdb  --std=c++11     -c $< -o $@

objconv: $(OBJ)
	clang++ $(CFLAGS) -ggdb  $^ -o $@

run: objconv
	./objconv cube.obja cube.objb

clean:
	rm -f objconf $(OBJ)
	rm -f Makefile.deps
