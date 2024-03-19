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

    printf("\nFilters:\n");
    printf("\nFor Original                                   enter : 0\n");
    printf("\nFor Graystyle                                  enter : 1\n");
    printf("\nFor Blur                                       enter : 2\n");
    printf("\nFor Sharp                                      enter : 3\n");
    printf("\nFor sobelEdgeDetection(currently misfuntional) enter : 4\n");
    printf("\nFor Reflector                                  enter : 5\n");
    printf("\nFor Negative                                   enter : 6\n");
    printf("\nPlease select the Filter for the Image : ");
    scanf("%d", &filterIndex);

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

    if(filterIndex==0)strcat(outputFilename, "_orig.bmp");
    else
    if(filterIndex==2)strcat(outputFilename, "_blur.bmp");
    else
    if(filterIndex==1)strcat(outputFilename, "_gray.bmp");
    else
    if(filterIndex==3)strcat(outputFilename, "_sharp.bmp");
    else
    if(filterIndex==4)strcat(outputFilename, "_edge.bmp");
    else
    if(filterIndex==5)strcat(outputFilename, "_reflected.bmp");
    else
    if(filterIndex==6)strcat(outputFilename, "_negative.bmp");

    copy(path,outputFilename);

    img = getImageData(path);
    if (!img)
     return;

    filter(img,filterIndex);

    writeImage(path, outputFilename, formatIndex,img);

    printf("\nNew filtered image has been created at %s",outputFilename);
}
