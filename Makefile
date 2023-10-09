CC = gcc
CFLAGS = -Wall -Wextra -ggdb
TARGET = image

BITMAP_PATH = bitmap
JPEG_PATH = jpeg

all: bitmap jpeg
image: all

bitmap: $(BITMAP_PATH)/*.c $(BITMAP_PATH)/*.h
	$(CC) -lm $(CFLAGS) $(BITMAP_PATH)/$(TARGET)_bitmap.c $(BITMAP_PATH)/bitmap.c -o $(TARGET)

jpeg: $(JPEG_PATH)/*.c $(JPEG_PATH)/*.h
	$(CC) $(CFLAGS) $(JPEG_PATH)/$(TARGET)_jpeg.c $(JPEG_PATH)/jpeg.c -o $(TARGET)

.PHONY: all bitmap jpeg
