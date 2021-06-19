src = $(wildcard ./src/*.cpp)
obj = $(patsubst ./src/%.cpp, ./obj/%.o, $(src))

inc_path = ./inc
myArgs= -Wall -g
target=server
CC=g++

ALL:$(target)

$(target):$(obj)
	$(CC) $^ -o $@ $(myArgs)

$(obj):./obj/%.o:./src/%.cpp
	$(CC) -c $^ -o $@ $(myArgs) -I $(inc_path)

clean:
	-rm -rf $(obj) $(target)

.PHONY: clean ALL

