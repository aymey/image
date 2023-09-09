CC = gcc
CFLAGS = -Wall -g -lm
TARGET = image

all: image

image: *.c *.h
	$(CC) $(CFLAGS) $(TARGET).c bitmap.c -o $(TARGET)

.PHONY: all image
