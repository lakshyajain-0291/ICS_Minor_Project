#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifndef STRUCTURE_H
#define STRUCTURE_H

typedef struct 
{
    int height;
    int width;
    int bytesPerPixel;
    int max_value;
    unsigned char *pixel_value;
}Image;

#endif

// Structure for BMP file header
// typedef struct {
//     unsigned short type;            // Magic identifier: "BM"
//     unsigned int size;              // File size in bytes
//     unsigned short reserved1;       // Reserved
//     unsigned short reserved2;       // Reserved
//     unsigned int offset;            // Offset to image data
// } BMPFileHeader;

// // Structure for BMP bitmap header
// typedef struct {
//     unsigned int size;              // Header size in bytes
//     int width;                      // Image width
//     int height;                     // Image height
//     unsigned short planes;          // Number of color planes
//     unsigned short bit_count;       // Bits per pixel
//     unsigned int compression;      // Compression type
//     unsigned int bitmap_size;      // Image size in bytes
//     int x_resolution;               // Pixels per meter, horizontal
//     int y_resolution;               // Pixels per meter, vertical
//     unsigned int colors_used;      // Number of colors in the palette
//     unsigned int colors_important; // Important colors
// } BMPBitmapHeader;

// typedef struct 
// {
//     BMPBitmapHeader *bitmap_header;
//     BMPFileHeader *file_header;
//     unsigned char *color_table;
//     int bytesPerPixel;
//     int max_value;
//     unsigned char *pixel_value;
// }Image;
