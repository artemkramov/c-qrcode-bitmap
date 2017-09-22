#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "qrcodegen.h"
#include "worker.h"


// The main application program.
int main(void) {
    int size = 100; // size of sides in pixels
    const char* fileName = "qrcode.bmp"; // path where file will be saved
    int width = size, height = size; //set width and height of the image
    int dpi = 96; // set dots per inch
    const char* text = "HELLO WORLD!!"; //text to be encoded
    printQRCode(fileName, width, height, dpi, text);
	return EXIT_SUCCESS;
}
