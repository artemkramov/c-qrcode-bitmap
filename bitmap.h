/*H****************************
* Library for bitmap creation
*H*/

#ifndef BITMAP_H_INCLUDED
#define BITMAP_H_INCLUDED

/**
* Structure which defines
* every pixel in the bitmap matrix
*/
typedef struct {
    float r, g, b;
} rgbData;

/**
* Save bitmap image by the given pixel array
*/
void saveBitmap(const char *fileName, int width, int height, int dpi, rgbData* pixelData);

#endif // BITMAP_H_INCLUDED
