SOURCE=bdd.cpp formula.cpp test.cpp
TARGET=test

CFLAGS = -I. -Wall -std=c++17

all: $(TARGET)

$(TARGET): $(SOURCE)
	g++ $(CFLAGS) -o $@ -I. $^

run:
	./$(TARGET)

clean:
	rm -rf $(TARGET)

