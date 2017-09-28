#include <stdlib.h>
#include "worker.h"
#include "qrcodegen.h"

#define CORRECTION_VALUE 32 // correction value to generate each bitmap value
#define RGB_MAX 255
#define RGB_MIN 0

/**
* Print QR code
*/
bool printQRCode(const char *fileName, int pixelPerQuadrant, const char *text) {

    // Set error correction level
    enum qrcodegen_Ecc errorCorrecrionLevel = qrcodegen_Ecc_LOW;

	// Make and print the QR Code symbol
	uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
	uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];

	// Convert text to QR code
	// Result is retrieved as a matrix
	bool isEncoded = qrcodegen_encodeText(text, tempBuffer, qrcode, errorCorrecrionLevel,
		qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
	if (isEncoded) {
        // Make width correction
        // As our bitmap is 24-bit the width length must be multiple of four
        // The size of each row is rounded up to a multiple of 4 bytes (a 32-bit DWORD) by padding.
        // Padding bytes (not necessarily 0) must be appended to the end of the rows in order to bring up
        // the length of the rows to a multiple of four bytes.
        // Get count of squares per row/column in QR code
        // Count is a changeable value and depends on text complexity
        // For more information see: http://www.qrcode.com/en/about/version.html
        int size = qrcodegen_getSize(qrcode);
        int widthCorrected = pixelPerQuadrant * size;
        int width = widthCorrected + (CORRECTION_VALUE - (widthCorrected % CORRECTION_VALUE));
        int height = widthCorrected;

        // Render pixel data
        rgbData* pixels = preparePixelMatrix(qrcode, width, height);
		// Create bitmap image
		saveBitmap(fileName, width, height, widthCorrected, pixels);
		return true;
	}
	else {
        return false;
	}

}

/**
* Prepare pixels array to fill bitmap
*/
rgbData* preparePixelMatrix(const uint8_t qrcode[], int width, int height) {
    // Get count of squares per row/column in QR code
    // Count is a changeable value and depends on text complexity
    // For more information see: http://www.qrcode.com/en/about/version.html
    int size = qrcodegen_getSize(qrcode);

    // Find smaller side to generate the scale factor
    int smallerSide = (width > height) ? height : width;

    // Scale factor helps to scale the QR modules to fit image
	int scaleFactor = smallerSide / size;
	rgbData *pixels = malloc(width * height * sizeof(rgbData));

	// Difference between size and QR code size itself
	// Is used to raise image to the top
	int differ = height - (scaleFactor * size);


	// Go through QR modules
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            // Get the module color
            bool isBlack = qrcodegen_getModule(qrcode, x ,y);

            // Count how much pixels each module has to fit
            int startX = x * scaleFactor;
            int startY = y * scaleFactor;
            int endX = startX + scaleFactor;
            int endY = startY + scaleFactor;
            for (int i = startX; i < endX; i++) {
                for (int j = startY; j < endY; j++) {
                    int a = (i + differ) * width + j;
                    pixels[a].r = RGB_MAX;
                    if (isBlack) {
                        pixels[a].r = RGB_MIN;
                    }

                }
            }
        }
    }
    // Set white pixels for extra horizontal lines
    for (int i = size * scaleFactor; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int a = i * width + j;
        }
    }
    // Set white pixels for extra vertical lines
    for (int i = 0; i < height; i++) {
        for (int j = size * scaleFactor; j < width; j++) {
            int a = i * width + j;
            pixels[a].r = RGB_MAX;
        }
    }
    return pixels;
}
