# Image Filtration Program

This document provides a comprehensive overview of the image filtration program, including explanations of the implemented filters and usage instructions.

## Installation

The program requires no specific installation process. You can compile the source code (image_filtration.c) using a C compiler like GCC and then execute the generated binary.

## Usage

1. Compile the code:

```bash
gcc b23cs1032.c -o b23cs1032
```

2. Run the program:

```bash
./b23cs1032
```

The program will prompt you for the following information:

- Image Format: Choose the format of your image (1 for PGM, 2 for BMP).
- Filter Selection: Select the desired filter by entering the corresponding number:
    1. Grayscale
    2. Blur
    3. Sharpen
    4. Sobel Edge Detection
    5. Reflect (mirror image horizontally)
    6. Negative

The program will process the image with the chosen filter and create a new file with the original filename appended with "_new" and the corresponding format extension (".pgm" or ".bmp").

## Known Issues

Currently, some filters may not work as expected on all the images due to the different bit makeup of each image. The filters have been designed with a certain bit makeup in mind, and images that do not match this makeup may not be processed correctly. I will be working on making the filters more robust to handle a wider range of images.
Other than 24 bit BMP type format file other formats are not supported currently as their data makeup is very complex.

## Features

- **Read and Write Images**: The project can read and write images in 24 bit BMP formats. The `getImageData` function reads an image from a file and stores pixel data  in an `Image` object. The `writeImage` function writes an image from an `Image` object to a file.

- **Image Filtration**: The project includes a function to apply a filter to an image and save the filtered image as a new file. The `filter` function applies a filter to an `Image` object, and the filtered image is saved with a `_new` suffix added to the original file name.

- **Grayscale Filter**: The project includes a grayscale filter that can convert a color image to grayscale.

- **Blur Filter**: The project includes a blur filter that can blur an image.

- **Sharp Filter**: The project includes a sharp filter that can sharpen an image.

- **Sobel Edge Detection Filter**: The project includes a Sobel edge detection filter that can detect edges in an image.

- **Reflector Filter**: The project includes a reflector filter that can reflect an image.

- **Negative Filter**: The project includes a negative filter that can make the colors complementary an image.

## Resources Used

- **Github Repositories**: eg-
[Github](https://github.com/abhijitnathwani/image-processing)

- **Books**: eg-
[Link to Book](https://homepages.inf.ed.ac.uk/rbf/BOOKS/PHILLIPS/cips2ed.pdf)

- **Websites**: eg-
[Site](https://codereview.stackexchange.com/questions/240836/cs50-pset4-filter-image-filters-in-c)


- **Blogs**: eg-
[Blog](https://abhijitnathwani.github.io/blog/2017/12/19/Introduction-to-Image-Processing-using-C)

- **Other References**: eg-
[Reference](https://skobki.com/en/c-language-apply-a-filter-to-an-image/#google_vignette)

