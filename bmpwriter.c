
// This file takes image data and writes it to a bitmap file
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const int FILE_HEADER_SIZE = 14;
const int INFO_HEADER_SIZE = 40;

void generateBitmapImage(unsigned char* image, int height, int width, char* img_filename);
unsigned char* createBitmapFileHeader(int height, int stride);
unsigned char* createBitmapInfoHeader(int height, int width);

// Constant values
FILE *fp;   // File to write to
int image_width;    // Pixel width of image
int byte_width;     // Bytes per line
int padding_size;   // Padding size
unsigned char padding[3] = {0, 0, 0};   // Padding
int stride;     // Stride (unecessary?)

// Initializes the filewriter to write to the given file
int 
init_writer(int image_wid, int image_height, char *filename) {

        // Generate necessary values
        image_width = image_wid;
        byte_width = image_wid * 3;
        padding_size = (4 - (byte_width) % 4) % 4;
        stride = byte_width + padding_size;

        // Open file
        fp = fopen(filename, "wb");

        // Write headers
        unsigned char* fileHeader = createBitmapFileHeader(image_height, stride);
        fwrite(fileHeader, 1, FILE_HEADER_SIZE, fp);

        unsigned char* infoHeader = createBitmapInfoHeader(image_height, image_width);
        fwrite(infoHeader, 1, INFO_HEADER_SIZE, fp);

        // Return 0 when done
        return 0;
}

// Writes a single line of the image to the file
int 
write_line(unsigned char *image) {
        fwrite(image, 3, image_width, fp);
        fwrite(padding, 1, padding_size, fp);
        return 0;
}

// Cleans up files
int 
close_writer() {
    fclose(fp);
    return 0;
}

// Created a .bmp file with the given filename containing pixel data from image
int 
display(unsigned char *image, int image_height)
{

        for (int i = 0; i < image_height; i++) {
                fwrite(image + (i*byte_width), 3, image_width, fp);
                fwrite(padding, 1, padding_size, fp);
        }
        // Return 0 on success
        return 0;
}


unsigned char* createBitmapFileHeader (int height, int stride)
{
    int fileSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (stride * height);

    static unsigned char fileHeader[] = {
        0,0,     /// signature
        0,0,0,0, /// image file size in bytes
        0,0,0,0, /// reserved
        0,0,0,0, /// start of pixel array
    };

    fileHeader[ 0] = (unsigned char)('B');
    fileHeader[ 1] = (unsigned char)('M');
    fileHeader[ 2] = (unsigned char)(fileSize      );
    fileHeader[ 3] = (unsigned char)(fileSize >>  8);
    fileHeader[ 4] = (unsigned char)(fileSize >> 16);
    fileHeader[ 5] = (unsigned char)(fileSize >> 24);
    fileHeader[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);

    return fileHeader;
}

unsigned char* createBitmapInfoHeader (int height, int width)
{
    static unsigned char infoHeader[] = {
        0,0,0,0, /// header size
        0,0,0,0, /// image width
        0,0,0,0, /// image height
        0,0,     /// number of color planes
        0,0,     /// bits per pixel
        0,0,0,0, /// compression
        0,0,0,0, /// image size
        0,0,0,0, /// horizontal resolution
        0,0,0,0, /// vertical resolution
        0,0,0,0, /// colors in color table
        0,0,0,0, /// important color count
    };

    infoHeader[ 0] = (unsigned char)(INFO_HEADER_SIZE);
    infoHeader[ 4] = (unsigned char)(width      );
    infoHeader[ 5] = (unsigned char)(width >>  8);
    infoHeader[ 6] = (unsigned char)(width >> 16);
    infoHeader[ 7] = (unsigned char)(width >> 24);
    infoHeader[ 8] = (unsigned char)(height      );
    infoHeader[ 9] = (unsigned char)(height >>  8);
    infoHeader[10] = (unsigned char)(height >> 16);
    infoHeader[11] = (unsigned char)(height >> 24);
    infoHeader[12] = (unsigned char)(1);
    infoHeader[14] = (unsigned char)(3*8);

    return infoHeader;
}