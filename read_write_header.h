#include"structure.h"

void freeImage(Image *img) {
    if (img) {
        if (img->pixel_value)free(img->pixel_value);

        free(img);
    }
}

void printImageFile(char *path)
{
    FILE *file=fopen(path,"rb");
    if(!file)
    {
        fprintf(stderr, "Error: Unable to open file %s\n", path);    
        return;
    }

    char c;
    printf("|||");
    while((c=fgetc(file))!=EOF)
    {
        printf("%d ",c);
    }
    printf("|||");


    printf("\nImage File printed");
}

Image *readPGM(char *path)
{
    printImageFile(path);//To be removed
    FILE *file=fopen(path,"rb");
    if(!file)
    {
        fprintf(stderr, "Error: Unable to open file %s\n", path);    
        return NULL;
    }

    char magic[3];
    fscanf(file,"%s",magic);
    printf("%s",magic);

    if(magic[0]!='P' || (magic[1]!='5' && magic[1]!='2'))
    {
        fprintf(stderr, "Error: Not a PGM file\n");
        fclose(file);
        return NULL;
    }

    Image *img=(Image*)malloc(sizeof(Image)); 
    if(!img)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(file);
        free(img);
        return NULL;
    }

    fscanf(file, "%d %d %d", &img->width, &img->height, &img->max_value);
    fgetc(file); 

    img->pixel_value=( unsigned char*)malloc(sizeof(unsigned char)*img->height*img->width);
    if (!img->pixel_value) { 
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(file);
        free(img); 
        return NULL;
    }

    fread(img->pixel_value, sizeof(unsigned char), img->height * img->width, file);
    // int i,j;
    // for(i=0;i<img->height;i++)
    // {
    //     for(j=0;j<img->width;j++)
    //         img->pixel_value[i*img->width+j]=fgetc(file);
        
    // }

    fclose(file);
    return img;
}

void writePGM(char *input,char *output,Image *img)
{
    FILE *inputFile=fopen(input,"rb");
    if(!inputFile)
    {
        fprintf(stderr, "Error: Unable to open file %s\n", input);    
        return ;
    }

    FILE *outputFile=fopen(output,"wb");
    if(!outputFile)
    {
        fprintf(stderr, "Error: Unable to open file %s\n", output);    
        fclose(inputFile);
        return;
    }

    unsigned char header[256];
    size_t toRead=fread(header,sizeof(unsigned char),256,inputFile);
    fwrite(header,sizeof(unsigned char),toRead,outputFile);

    fwrite(img->pixel_value,sizeof(unsigned char),img->width*img->height,outputFile);

    fclose(inputFile);
    fclose(outputFile);
}

Image *readBMP(char *path)
{
    printImageFile(path);//To be removed
    FILE *file=fopen(path,"rb");
    if(!file)
    {
        fprintf(stderr, "Error: Unable to open file |%s|\n", path);    
        return NULL;
    }

    Image *img=(Image*)malloc(sizeof(Image)); 
    if(!img)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(file);
        free(img);
        return NULL;
    }

    fseek(file,18,SEEK_SET);
    fread(&img->width,sizeof(int),1,file);
    fseek(file,22,SEEK_SET);
    fread(&img->height,sizeof(int),1,file);
    fseek(file,28,SEEK_SET);
    fread(&img->bytesPerPixel,sizeof(int),1,file);

    img->bytesPerPixel/=8;
    printf(" %d %d %d",img->height,img->width,img->bytesPerPixel);
    int bytesperpixel=img->bytesPerPixel;

    img->pixel_value=( unsigned char*)malloc(sizeof(unsigned char)*img->height*img->width*bytesperpixel);
    if (!img->pixel_value) 
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(file);
        free(img);
        return NULL;
    }

    fseek(file,54,SEEK_SET);

    fread(img->pixel_value,sizeof(unsigned char),img->width*img->height*bytesperpixel,file);
    fclose(file);
    return img;
}

void writeBMP(char *input,char *output,Image *img)
{
    FILE *inputFile=fopen(input,"rb");
    if(!inputFile)
    {
        fprintf(stderr, "Error: Unable to open file %s\n", input);    
        return;
    }

    FILE *outputFile=fopen(output,"wb");
    if(!outputFile)
    {
        fprintf(stderr, "Error: Unable to open file %s\n", output);    
        return;
    }

    char header[54];

    fread(header,sizeof(unsigned char),54,inputFile);
    fwrite(header,sizeof(unsigned char),54,outputFile);
    
    int padding = (4 - (img->width * 3) % 4)%4;

    int i;
    for(i=0;i<img->height;i++)
    {
        fwrite(&img->pixel_value[i*img->width*3],sizeof(unsigned char),img->width*3,outputFile);
        unsigned char *padding_data=(unsigned char*)calloc(padding,sizeof(unsigned char));

        fwrite(padding_data,sizeof(unsigned char),padding,outputFile);
    }
    fclose(inputFile);
    fclose(outputFile);
}


void writeImage(char *input,char *output,int formatIndex,Image * img)
{
    if (formatIndex == 1)
        writePGM(input,output,img);
    else
    if (formatIndex == 2)
        writeBMP(input,output,img);
}

Image *readImage(char *input,int formatIndex)
{
    if (formatIndex == 1)
        return readPGM(input);

    if (formatIndex == 2)
        return readBMP(input);
}
