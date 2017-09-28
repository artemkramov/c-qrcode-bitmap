#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "qrcodegen.h"
#include "worker.h"
#include <locale.h>
#include <wchar.h>


// The main application program.
int main(void) {
    const char* fileName = "qrcode.bmp"; // path where file will be saved
    int pixelPerQuadrant = 3; // set pixels count per item
    const char* text = "Текст текст"; //text to be encoded
    printQRCode(fileName, pixelPerQuadrant, text);
    printf("%s\r\n", text);
	return EXIT_SUCCESS;
}
