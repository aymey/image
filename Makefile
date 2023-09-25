CC = gcc
CFLAGS = -Wall -g -lm
TARGET = image

BITMAP_PATH = ./bitmap

all: bitmap
image: all

bitmap: $(BITMAP_PATH)/*.c $(BITMAP_PATH)/*.h
	$(CC) $(CFLAGS) $(BITMAP_PATH)/$(TARGET)_bitmap.c $(BITMAP_PATH)/bitmap.c -o $(TARGET)

.PHONY: all bitmap
