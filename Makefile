# Make Makefile OS-agnostic
ifeq ($(OS),Windows_NT)
    RM = del /Q
    TARGET_EXT = .exe
    OBJ_FILES = src\*.o
	CFLAGS = -std=c11 -Wall -Wextra -O2 -Ilib/raylib
	LDFLAGS = -Llib/raylib -lraylib -lopengl32 -lgdi32 -lwinmm
else
    RM = rm -f
    TARGET_EXT =
    OBJ_FILES = $(OBJ)
	CFLAGS = -std=c11 -Wall -Wextra -O2 -I/opt/homebrew/include
	LDFLAGS = -L/opt/homebrew/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
endif

CC = gcc
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
	$(RM) $(TARGET)$(TARGET_EXT)
	$(RM) $(OBJ_FILES)