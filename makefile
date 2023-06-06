CC = gcc
CFLAGS = -std=c99 -lm -Wall -Werror -Wextra -pedantic
TARGET = t9search
SOURCE = t9search.c

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

.PHONY: clean

clean:
	rm -f $(TARGET)
