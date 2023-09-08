CC = gcc
CFLAGS = -Wall -g
TARGET = image

all: image

image: $(TARGET).c bitmap.c
	$(CC) $(CFLAGS) $(TARGET).c bitmap.c -o $(TARGET)

.PHONY: all image
