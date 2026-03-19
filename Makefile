CC = g++
CFLAGS = -lraylib -g
SRC = src/main.cpp \
	  src/Render.cpp \
	  src/Scene.cpp \
	  src/Parser.cpp

OBJ = $(SRC:.cpp=.o)
TARGET = vn

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean