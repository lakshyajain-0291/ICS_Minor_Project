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


// Function to read BMP file header
// void read_bmp_file_header(FILE *file, BMPFileHeader *file_header) {
//     fread(&file_header->type, sizeof(unsigned short), 1, file);
//     fread(&file_header->size, sizeof(unsigned int), 1, file);
//     fread(&file_header->reserved1, sizeof(unsigned short), 1, file);
//     fread(&file_header->reserved2, sizeof(unsigned short), 1, file);
//     fread(&file_header->offset, sizeof(unsigned int), 1, file);
// }

// // Function to read BMP bitmap header
// void read_bmp_bitmap_header(FILE *file, BMPBitmapHeader *bitmap_header) {
//     fread(&bitmap_header->size, sizeof(unsigned int), 1, file);
//     fread(&bitmap_header->width, sizeof(int), 1, file);
//     fread(&bitmap_header->height, sizeof(int), 1, file);
//     fread(&bitmap_header->planes, sizeof(unsigned short), 1, file);
//     fread(&bitmap_header->bit_count, sizeof(unsigned short), 1, file);
//     fread(&bitmap_header->compression, sizeof(unsigned int), 1, file);
//     fread(&bitmap_header->bitmap_size, sizeof(unsigned int), 1, file);
//     fread(&bitmap_header->x_resolution, sizeof(int), 1, file);
//     fread(&bitmap_header->y_resolution, sizeof(int), 1, file);
//     fread(&bitmap_header->colors_used, sizeof(unsigned int), 1, file);
//     fread(&bitmap_header->colors_important, sizeof(unsigned int), 1, file);
// }

// Image *readBMP(char *path)
// {
//     // Open BMP file for reading
//     FILE *file = fopen(path, "rb");
//     if (file == NULL) {
//         printf("Error opening file.");
//         return NULL;
//     }

//     Image *img = (Image *)malloc(sizeof(Image));
//     if (img == NULL) {
//         printf("Error allocating memory for Image.");
//         fclose(file);
//         return NULL;
//     }

//     // Allocate memory for BMP file header
//     img->file_header = (BMPFileHeader *)malloc(sizeof(BMPFileHeader));
//     if (img->file_header == NULL) {
//         printf("Error allocating memory for BMP file header.");
//         fclose(file);
//         free(img);
//         return NULL;
//     }

//     // Allocate memory for BMP bitmap header
//     img->bitmap_header = (BMPBitmapHeader *)malloc(sizeof(BMPBitmapHeader));
//     if (img->bitmap_header == NULL) {
//         printf("Error allocating memory for BMP bitmap header.");
//         fclose(file);
//         free(img->file_header);
//         free(img);
//         return NULL;
//     }

//     // Read BMP file header
//     read_bmp_file_header(file, img->file_header);

//     // Read BMP bitmap header
//     read_bmp_bitmap_header(file, img->bitmap_header);

//     img->color_table = (unsigned char *)malloc(img->bitmap_header->colors_used * 4);
//     if (img->color_table == NULL) {
//         printf("Error allocating memory for color table.");
//         fclose(file);
//         free(img->file_header);
//         free(img->bitmap_header);
//         free(img);
//         return NULL;
//     }

//     // Read color table
//     fread(img->color_table, sizeof(unsigned char), img->bitmap_header->colors_used * 4, file);

//     img->pixel_value = (unsigned char *)malloc(img->bitmap_header->bitmap_size);
//     if (img->pixel_value == NULL) {
//         printf("Error allocating memory for pixel data.");
//         fclose(file);
//         free(img->file_header);
//         free(img->bitmap_header);
//         free(img->color_table);
//         free(img);
//         return NULL;
//     }

//     // Read image data
//     fread(img->pixel_value, sizeof(unsigned char), img->bitmap_header->bitmap_size, file);

//     fclose(file);
//     return img;
// }

// void writeBMP(char *input,char *output,Image *img)
// {
//     // Open BMP file for writing
//     FILE *output_file = fopen(output, "wb");
//     if (output_file == NULL) {
//         printf("Error opening output file.");
//         return;
//     }

//     // Write BMP file header
//     fwrite(img->file_header, sizeof(BMPFileHeader), 1, output_file);

//     // Write BMP bitmap header
//     fwrite(img->bitmap_header, sizeof(BMPBitmapHeader), 1, output_file);

//     // Write color table
//     fwrite(img->color_table, sizeof(unsigned char), (img->bitmap_header)->colors_used * 4, output_file);

//     // Write image data
//     fwrite(img->pixel_value, sizeof(unsigned char), img->bitmap_header->bitmap_size, output_file);

//     // Close output file after writing
//     fclose(output_file);

//     // Free allocated memory
//     // free(image_data);

// }

// Image *readBMP(char *path)
// {
//     printImageFile(path);//To be removed
//     FILE *file=fopen(path,"rb");
//     if(!file)
//     {
//         fprintf(stderr, "Error: Unable to open file |%s|\n", path);    
//         return NULL;
//     }

//     Image *img=(Image*)malloc(sizeof(Image)); 
//     if(!img)
//     {
//         fprintf(stderr, "Error: Memory allocation failed\n");
//         fclose(file);
//         free(img);
//         return NULL;
//     }

//     fseek(file,18,SEEK_SET);
//     fread(&img->width,sizeof(int),1,file);
//     fseek(file,22,SEEK_SET);
//     fread(&img->height,sizeof(int),1,file);
//     fseek(file,28,SEEK_SET);
//     fread(&img->bytesPerPixel,sizeof(int),1,file);

//     img->bytesPerPixel/=8;
//     printf(" %d %d %d",img->height,img->width,img->bytesPerPixel);
//     int bytesperpixel=img->bytesPerPixel;

//     img->pixel_value=( unsigned char*)malloc(sizeof(unsigned char)*img->height*img->width*bytesperpixel);
//     if (!img->pixel_value) 
//     {
//         fprintf(stderr, "Error: Memory allocation failed\n");
//         fclose(file);
//         free(img);
//         return NULL;
//     }

//     fseek(file,54,SEEK_SET);

//     fread(img->pixel_value,sizeof(unsigned char),img->width*img->height*bytesperpixel,file);
//     fclose(file);
//     return img;
// }

// void writeBMP(char *input,char *output,Image *img)
// {
//     FILE *inputFile=fopen(input,"rb");
//     if(!inputFile)
//     {
//         fprintf(stderr, "Error: Unable to open file %s\n", input);    
//         return;
//     }

//     FILE *outputFile=fopen(output,"wb");
//     if(!outputFile)
//     {
//         fprintf(stderr, "Error: Unable to open file %s\n", output);    
//         return;
//     }

//     char header[54];

//     fread(header,sizeof(unsigned char),54,inputFile);
//     fwrite(header,sizeof(unsigned char),54,outputFile);
    
//     int padding = (4 - (img->width * 3) % 4)%4;

//     int i;
//     for(i=0;i<img->height;i++)
//     {
//         fwrite(&img->pixel_value[i*img->width*3],sizeof(unsigned char),img->width*3,outputFile);
//         unsigned char *padding_data=(unsigned char*)calloc(padding,sizeof(unsigned char));

//         fwrite(padding_data,sizeof(unsigned char),padding,outputFile);
//     }
//     fclose(inputFile);
//     fclose(outputFile);
// }


void copy(char *input,char *output)
{
    FILE *inputFile=fopen(input,"rb");
    if(!inputFile)
    {
        fprintf(stderr, "Error: Unable to open file %s\n", input);    
        return;
    }

    FILE *outputFile=fopen(output,"wb+");
    if(!outputFile)
    {
        fprintf(stderr, "Error: Unable to open file %s\n", output);    
        return;
    }

    // int bufferSize = 1024; // Define buffer size
    
    char buffer;
    size_t bytesRead=1;
    while (bytesRead>0) {
        bytesRead = fread(&buffer, 1, bytesRead, inputFile);
        fwrite(&buffer, 1, bytesRead, outputFile);
    }

}

Image *getImageData(char *input)
{
    FILE *inputFile=fopen(input,"rb");
    if(!inputFile)
    {
        fprintf(stderr, "Error: Unable to open file %s\n", input);    
        return;
    }

    Image *img=(Image*)malloc(sizeof(Image));

    
}

void writeImage(char *input,char *output,int formatIndex,Image * img)
{
    if (formatIndex == 1)
        writePGM(input,output,img);
    else
    if (formatIndex == 2);
        // write(input,output,img);
}

Image *readImage(char *input,int formatIndex)
{
    if (formatIndex == 1)
        return readPGM(input);

    if (formatIndex == 2);
        // return copy(input);
}
