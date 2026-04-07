CC = gcc

CFLAGS = -std=c11 -Wall -Wextra -O2 -Ilib/raylib
LDFLAGS = -Llib/raylib -lraylib -lopengl32 -lgdi32 -lwinmm

#CFLAGS = -std=c11 -Wall -Wextra -O2 -I/opt/homebrew/include
#LDFLAGS = -L/opt/homebrew/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

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