CC = gcc
CFLAGS = -Wall -g
TARGET = image

all: image

image: $(TARGET).c bitmap.h
	$(CC) $(CFLAGS) $(TARGET).c bitmap.h -o $(TARGET)

.PHONY: all image
