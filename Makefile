CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

SRC = main.c input.c output.c
OBJ = $(SRC:.c=.o)

HEADERS = project.h

TARGET = simonSays

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) -lsense

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)
