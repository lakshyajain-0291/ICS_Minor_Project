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