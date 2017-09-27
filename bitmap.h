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
    int r;
} rgbData;

/**
* Save bitmap image by the given pixel array
*/
void saveBitmap(const char *fileName, int width, int height, int widthCorrected, rgbData* pixelData);

#endif // BITMAP_H_INCLUDED
