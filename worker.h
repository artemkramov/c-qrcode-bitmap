/*H****************************
* Auxiliary header file to generate bitmap images
* based on QR code
*H*/

#ifndef WORKER_H_INCLUDED
#define WORKER_H_INCLUDED

#include <stdbool.h>
#include <stdint.h>
#include "bitmap.h"

/**
* Print QR code by the given text
* QR code can be with different version
* It depends on the text complexity
*/
bool printQRCode(const char *fileName, int width, int height, int dpi, const char *text);

/**
* Prepare pixel matrix for bitmap filling
* basing on the QR-conversation
*/
rgbData* preparePixelMatrix(const uint8_t qrcode[], int width, int height);

#endif // WORKER_H_INCLUDED
