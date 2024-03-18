# Image Processing Project

This project is about processing images in different formats such as PGM and BMP. It provides functionalities to read and write images, and apply various filters to them.

## Features

- **Read and Write Images**: The project can read and write images in PGM and BMP formats. The `readImage` function reads an image from a file and stores it in an `Image` object. The `writeImage` function writes an image from an `Image` object to a file.

- **Image Filtration**: The project includes a function to apply a filter to an image and save the filtered image as a new file. The `filter` function applies a filter to an `Image` object, and the filtered image is saved with a `_new` suffix added to the original file name.

- **Grayscale Filter**: The project includes a grayscale filter that can convert a color image to grayscale.

- **Blur Filter**: The project includes a blur filter that can blur an image.

- **Sharp Filter**: The project includes a sharp filter that can sharpen an image.

- **Sobel Edge Detection Filter**: The project includes a Sobel edge detection filter that can detect edges in an image.

- **Reflector Filter**: The project includes a reflector filter that can reflect an image.

## Known Issues

Currently, some filters may not work as expected due to the different bit makeup of each image. The filters have been designed with a certain bit makeup in mind, and images that do not match this makeup may not be processed correctly. I will be working on making the filters more robust to handle a wider range of images.

## Usage

The main functions in this project are `readImage` and `writeImage`.

`readImage` takes an input file name and a format index as arguments. The format index should be 1 for PGM images and 2 for BMP images. It returns an `Image` object that contains the pixel data of the image.

`writeImage` takes an input file name, an output file name, a format index, and an `Image` object as arguments. It writes the image data from the `Image` object to the output file.

The `filter` function applies a filter to an `Image` object. The filter index should be between 1 and 5, inclusive. Each index corresponds to a different filter:

- 1: Grayscale filter
- 2: Blur filter
- 3: Sharp filter
- 4: Sobel edge detection filter
- 5: Reflector filter

After applying a filter, the `writeImage` function is used to save the filtered image as a new file. The new file has the same name as the original file, with a `_new` suffix added before the file extension.

## Building

This project is written in C. You can compile it with any C compiler. For example, if you're using gcc, you can compile the project with the following command:

```bash
gcc -o imgproc main.c read_write_header.c -lm