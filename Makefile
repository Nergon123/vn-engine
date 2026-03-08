CC = g++
CFLAGS = -lraylib
SRC = src/main.cpp \
	  src/Render.cpp

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