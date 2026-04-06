CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -O2 -Ilib/raylib
LDFLAGS = -Llib/raylib -lraylib -lopengl32 -lgdi32 -lwinmm

TARGET = chess-engine
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJ)