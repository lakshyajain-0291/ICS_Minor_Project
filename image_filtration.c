#include "read_write_header.h"
#include "filters.h"

#define MAX 200

void main()
{
    char path[MAX];
    char *outputFilename;
    int formatIndex, filterIndex;
    Image *img;

    printf("\nPlease enter the address of Image      : ");
    fgets(path,200,stdin);
    strtok(path, "\n"); // Remove trailing newline

    printf("\nPlease select the Format of the Image  : ");
    scanf("%d", &formatIndex);

    printf("\nPlease select the Filter for the Image : ");
    scanf("%d", &filterIndex);

    // img = readImage(path,formatIndex);
    // if (!img)
        // return;

    outputFilename = (char *)malloc(strlen(path) + 10);
    if (!outputFilename)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        freeImage(img);
        return;
    }

    strcpy(outputFilename, path);
    char *dot = strrchr(outputFilename, '.');
    *dot = 0;

    if(formatIndex==1)strcat(outputFilename, "_new.pgm");
    else
    if(formatIndex==2)strcat(outputFilename, "_new.bmp");

    copy(path,outputFilename);

    img=getImageData(path,formatIndex);

    filter(img,filterIndex);

    writeImage(path, outputFilename, formatIndex,img);

    printf("\nNew filtered image has been created at %s",outputFilename);
}
