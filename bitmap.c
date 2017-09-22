#include "bitmap.h"
#include <stdio.h>
#include <string.h>

#define BITMAP_HEADER_SIZE 54 //bytes
#define BITMAP_FILE_HEADER_SIZE 14 //bytes
#define BITMAP_BIT_PER_PIXEL 24
#define BITMAP_DPI_SCALE 39.375

void saveBitmap(const char *fileName, int width, int height, int dpi, rgbData* pixelData) {
    // create a file object that we will use to write our image
    FILE *image;
    // we want to know how many pixels to reserve
    int imageSize = width * height;
    // a byte is 4 bits but we are creating a 24 bit image so we can represent a pixel with 3
    // our final file size of our image is the width * height * 4 + size of bitmap header
    int fileSize = BITMAP_HEADER_SIZE + 4 * imageSize;
    // pixels per meter https://www.wikiwand.com/en/Dots_per_inch
    int ppm = dpi * BITMAP_DPI_SCALE;

    // bitmap file header (14 bytes)
    // we could be savages and just create 2 array but since this is for learning lets
    // use structs so it can be parsed by someone without having to refer to the spec

    // since we have a non-natural set of bytes, we must explicitly tell the
    // compiler to not pad anything, on gcc the attribute alone doesn't work so
    // a nifty trick is if we declare the smallest data type last the compiler
    // *might* ignore padding, in some cases we can use a pragma or gcc's
    // __attribute__((__packed__)) when declaring the struct
    // we do this so we can have an accurate sizeof() which should be 14, however
    // this won't work here since we need to order the bytes as they are written
    struct bitmapFileHeader {
        unsigned char   bitmapType[2];     // 2 bytes
        int             fileSize;          // 4 bytes
        short           reserved1;         // 2 bytes
        short           reserved2;         // 2 bytes
        unsigned int    offsetBits;        // 4 bytes
    } fileHeader;

    // bitmap image header (40 bytes)
    struct bitmapImageHeader {
        unsigned int    sizeHeader;        // 4 bytes
        unsigned int    width;             // 4 bytes
        unsigned int    height;            // 4 bytes
        short int       planes;            // 2 bytes
        short int       bitCount;          // 2 bytes
        unsigned int    compression;       // 4 bytes
        unsigned int    imageSize;         // 4 bytes
        unsigned int    ppmX;              // 4 bytes
        unsigned int    ppmY;              // 4 bytes
        unsigned int    clrUsed;           // 4 bytes
        unsigned int    clrImportant;      // 4 bytes
    } imageHeader;

    // if you are on Windows you can include <windows.h>
    // and make use of the BITMAPFILEHEADER and BITMAPINFOHEADER structs
    memcpy(&fileHeader.bitmapType, "BM", 2);
    fileHeader.fileSize       = fileSize;
    fileHeader.reserved1      = 0;
    fileHeader.reserved2      = 0;
    fileHeader.offsetBits     = 0;

    imageHeader.sizeHeader    = sizeof(imageHeader);
    imageHeader.width         = width;
    imageHeader.height        = height;
    imageHeader.planes        = 1;
    imageHeader.bitCount      = BITMAP_BIT_PER_PIXEL;
    imageHeader.compression   = 0;
    imageHeader.imageSize     = fileSize;
    imageHeader.ppmX          = ppm;
    imageHeader.ppmY          = ppm;
    imageHeader.clrUsed       = 0;
    imageHeader.clrImportant  = 0;

    image = fopen(fileName, "wb");

    // compiler woes so we will just use the constant 14 we know we have
    fwrite(&fileHeader, 1, BITMAP_FILE_HEADER_SIZE, image);
    fwrite(&imageHeader, 1, sizeof(imageHeader), image);

    // write out pixel data, one last important this to know is the ordering is backwards
    // we have to go BGR as opposed to RGB
    for (int i = 0; i < imageSize; i++) {
       rgbData BGR = pixelData[i];

       float red   = (BGR.r);
       float green = (BGR.g);
       float blue  = (BGR.b);

       // if you don't follow BGR image will be flipped!
       unsigned char color[3] = {
           blue, green, red
       };
       fwrite(color, 1, sizeof(color), image);
    }
    fclose(image);
}
