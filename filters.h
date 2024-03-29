#include"structure.h"
#include<math.h>

void grayscale(Image *img)
{
    int i,j,avg;
    int dataLen=img->height*img->width*img->bytesPerPixel;
    for(i=0;i<dataLen;i+=img->bytesPerPixel)
    {
        for(j=0,avg=0;j<img->bytesPerPixel;j++)
         avg+=img->pixel_value[i+j];

        for(j=0,avg/=img->bytesPerPixel;j<img->bytesPerPixel;j++)
         img->pixel_value[i+j]=avg;

    }
}

void blur(Image *img)
{
    int dataLen=img->height*img->width*img->bytesPerPixel;
    int i,j,k,sum;
    unsigned char *tmp = (unsigned char*)malloc(sizeof(unsigned char) * dataLen);
    if (tmp == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        return;
    }
    
    memcpy(tmp,img->pixel_value,dataLen);

    for(i=1;i<img->height-1;i++)
    {
        for(j=1;j<img->width-1;j++)
        {
            for(k=0;k<img->bytesPerPixel;k++)
            {
                sum=0;
                sum=tmp[(i - 1) * img->width * img->bytesPerPixel + (j - 1) * img->bytesPerPixel + k] +
                    tmp[(i - 1) * img->width * img->bytesPerPixel + j * img->bytesPerPixel + k] +
                    tmp[(i - 1) * img->width * img->bytesPerPixel + (j + 1) * img->bytesPerPixel + k] +
                    tmp[i * img->width * img->bytesPerPixel + (j - 1) * img->bytesPerPixel + k] +
                    tmp[i * img->width * img->bytesPerPixel + j * img->bytesPerPixel + k] +
                    tmp[i * img->width * img->bytesPerPixel + (j + 1) * img->bytesPerPixel + k] +
                    tmp[(i + 1) * img->width * img->bytesPerPixel + (j - 1) * img->bytesPerPixel + k] +
                    tmp[(i + 1) * img->width * img->bytesPerPixel + j * img->bytesPerPixel + k] +
                    tmp[(i + 1) * img->width * img->bytesPerPixel + (j + 1) * img->bytesPerPixel + k];

                sum /= 9;

                img->pixel_value[i * img->width * img->bytesPerPixel + j * img->bytesPerPixel + k] = (unsigned char)sum;
            }
        }
    }
    free(tmp);
}



void sharp(Image *img)
{
    // Sharping Mask:
    //                     {-1, -1, -1},
    //                     {-1,  9, -1},
    //                     {-1, -1, -1}};
    
    int i,j,k,sum,m,n;
    int dataLen=img->height*img->width*img->bytesPerPixel;
    unsigned char *tmp=(unsigned char*)malloc(sizeof(unsigned char)*dataLen);
    memcpy(tmp, img->pixel_value, dataLen); 
    int mask[3][3] = {{-1, -1, -1},
                      {-1,  9, -1},
                      {-1, -1, -1}};
    
    for (i = 1; i < img-> height - 1; i++) {
        for (j = 1; j < img->width - 1; j++) {
            for (k = 0; k < img->bytesPerPixel; k++) {
                sum = 0;
                for (m = -1; m <= 1; m++) {
                    for (n = -1; n <= 1; n++) {
                        sum += mask[m + 1][n + 1] * 
                            tmp[(i + m) * img->width * img->bytesPerPixel + (j + n) * img->bytesPerPixel + k];
                    }
                }
                sum = fmin(255, fmax(0, sum)); 
                img->pixel_value[i * img->width * img->bytesPerPixel + j * img->bytesPerPixel + k] = 
                    (unsigned char) sum;
            }
        }
    }

    free(tmp);

}

void reflector(Image *img)
{
    int dataLen=img->height*img->width*img->bytesPerPixel;
    int i,j,k;
    unsigned char *tmp=(unsigned char*)malloc(sizeof(unsigned char)*dataLen);
    memcpy(tmp,img->pixel_value,dataLen);

    for(i=0;i<img->height;i++)
    {
        for(j=0;j<img->width;j++)
        {
            for(k=0;k<img->bytesPerPixel;k++)
                img->pixel_value[i * img->width * img->bytesPerPixel + j * img->bytesPerPixel + k]=tmp[i * img->width * img->bytesPerPixel + (img->width-j-1) * img->bytesPerPixel + k];
        }
    }
    free(tmp);
}

void sobelEdgeDetection(Image *img)
{   
    // Sobel kernels
    // Sobel_X = [-1, 0, 1; -2, 0, 2; -1, 0, 1]
    // Sobel_Y = [-1, -2, -1; 0, 0, 0; 1, 2, 1]

    int dataLen=img->height*img->width*img->bytesPerPixel;
    int i,j,k,sum;
    int Gx,Gy;
    int G;
    unsigned char *tmp=(unsigned char*)malloc(sizeof(unsigned char)*dataLen);
    memcpy(tmp,img->pixel_value,dataLen);

    for(i=1;i<img->height-1;i++)
    {
        for(j=1;j<img->width-1;j++)
        {
            for(k=0;k<img->bytesPerPixel;k++)
            {
                Gx= tmp[(i - 1) * img->width * img->bytesPerPixel + (j - 1) * img->bytesPerPixel + k]*(-1) +
                    tmp[(i - 1) * img->width * img->bytesPerPixel + j * img->bytesPerPixel + k]*(0) +
                    tmp[(i - 1) * img->width * img->bytesPerPixel + (j + 1) * img->bytesPerPixel + k]*(1) +
                    tmp[i * img->width * img->bytesPerPixel + (j - 1) * img->bytesPerPixel + k]*(-2) +
                    tmp[i * img->width * img->bytesPerPixel + j * img->bytesPerPixel + k]*(0) +
                    tmp[i * img->width * img->bytesPerPixel + (j + 1) * img->bytesPerPixel + k]*(2) +
                    tmp[(i + 1) * img->width * img->bytesPerPixel + (j - 1) * img->bytesPerPixel + k]*(-1) +
                    tmp[(i + 1) * img->width * img->bytesPerPixel + j * img->bytesPerPixel + k]*(0) +
                    tmp[(i + 1) * img->width * img->bytesPerPixel + (j + 1) * img->bytesPerPixel + k]*(1);

                Gy= tmp[(i - 1) * img->width * img->bytesPerPixel + (j - 1) * img->bytesPerPixel + k]*(-1) +
                    tmp[(i - 1) * img->width * img->bytesPerPixel + j * img->bytesPerPixel + k]*(-2) +
                    tmp[(i - 1) * img->width * img->bytesPerPixel + (j + 1) * img->bytesPerPixel + k]*(-1) +
                    tmp[i * img->width * img->bytesPerPixel + (j - 1) * img->bytesPerPixel + k]*(0) +
                    tmp[i * img->width * img->bytesPerPixel + j * img->bytesPerPixel + k]*(0) +
                    tmp[i * img->width * img->bytesPerPixel + (j + 1) * img->bytesPerPixel + k]*(0) +
                    tmp[(i + 1) * img->width * img->bytesPerPixel + (j - 1) * img->bytesPerPixel + k]*(1) +
                    tmp[(i + 1) * img->width * img->bytesPerPixel + j * img->bytesPerPixel + k]*(2) +
                    tmp[(i + 1) * img->width * img->bytesPerPixel + (j + 1) * img->bytesPerPixel + k]*(1);

                G=sqrt(Gx*Gx+Gy*Gy);
                G = (G > 255) ? 255 : G;
                img->pixel_value[i * img->width * img->bytesPerPixel + j * img->bytesPerPixel + k]=G;
            }
        }
    }
    free(tmp);
}

void negativeImage(Image *img)
{
    int dataLen=img->height*img->width*img->bytesPerPixel;
    int i;
    for(i=0;i<dataLen;i++)
        img->pixel_value[i]=255-img->pixel_value[i];
}

void filter(Image *img,int filterIndex)
{
    if(filterIndex<0 || filterIndex>6)
    {
        printf("\nInvalid Filter Index");
        return;
    }
    else if(filterIndex==0)
        return;
    else if (filterIndex == 1)
        grayscale(img);
    else if (filterIndex == 2)
        blur(img);
    else if (filterIndex == 3)
        sharp(img);
    else if (filterIndex == 4)
        sobelEdgeDetection(img);
    else if (filterIndex == 5)
        reflector(img);
    else if (filterIndex == 6)
        negativeImage(img);
}

// void blur(Image *img) {
//     int dataLen = img->height * img->width * img->bytesPerPixel;
//     unsigned char *tmp = (unsigned char*)malloc(sizeof(unsigned char) * dataLen);
//     memcpy(tmp, img->pixel_value, dataLen);

//     for (int i = 1; i < img->height - 1; i++) {
//         for (int j = 1; j < img->width - 1; j++) {
//             for (int k = 0; k < img->bytesPerPixel; k++) {
//                 int sum = 0;
//                 for (int di = -1; di <= 1; di++) {
//                     for (int dj = -1; dj <= 1; dj++) {
//                         sum += tmp[(i + di) * img->width * img->bytesPerPixel + (j + dj) * img->bytesPerPixel + k];
//                     }
//                 }
//                 img->pixel_value[i * img->width * img->bytesPerPixel + j * img->bytesPerPixel + k] = sum / 9;
//             }
//         }
//     }

//     free(tmp);
// }
