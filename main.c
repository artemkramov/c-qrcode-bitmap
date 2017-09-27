#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "qrcodegen.h"
#include "worker.h"


// The main application program.
int main(void) {
    int size = 200; // size of sides in pixels
    const char* fileName = "qrcode.bmp"; // path where file will be saved
    int width = size, height = size; //set width and height of the image
    const char* text = "The color table (palette) The color table (palette) The color table (palette) The color table (palette)"; //text to be encoded
    printQRCode(fileName, width, height, text);
	return EXIT_SUCCESS;
}
