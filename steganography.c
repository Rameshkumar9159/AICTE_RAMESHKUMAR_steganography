#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "steganography.h"

#define BMP_HEADER_SIZE 54  // Standard BMP header size

/**
 * Embeds data into a BMP file using LSB (Least Significant Bit) steganography.
 */
int embed_data(const char *input_bmp, const char *output_bmp, const char *data_file) {
    FILE *bmp = fopen(input_bmp, "rb");
    FILE *newBmp = fopen(output_bmp, "wb");
    FILE *data = fopen(data_file, "rb");

    if (!bmp || !newBmp || !data) {
        fprintf(stderr, "Error opening files.\n");
        return 1;
    }

    // Copy BMP header
    unsigned char header[BMP_HEADER_SIZE];
    fread(header, sizeof(unsigned char), BMP_HEADER_SIZE, bmp);
    fwrite(header, sizeof(unsigned char), BMP_HEADER_SIZE, newBmp);

    // Embed message
    unsigned char pixel;
    char messageChar;
    int bitIndex = 0;

    printf("Embedding message: ");
    while (fread(&messageChar, sizeof(char), 1, data)) {
        printf("%c", messageChar);  // Display the message being embedded
        for (int i = 0; i < 8; i++) {
            fread(&pixel, sizeof(unsigned char), 1, bmp);
            pixel = (pixel & 0xFE) | ((messageChar >> i) & 1);
            fwrite(&pixel, sizeof(unsigned char), 1, newBmp);
        }
    }
    printf("\n");

    // Null terminate message
    messageChar = '\0';
    for (int i = 0; i < 8; i++) {
        fread(&pixel, sizeof(unsigned char), 1, bmp);
        pixel = (pixel & 0xFE) | ((messageChar >> i) & 1);
        fwrite(&pixel, sizeof(unsigned char), 1, newBmp);
    }

    // Copy remaining BMP data
    while (fread(&pixel, sizeof(unsigned char), 1, bmp)) {
        fwrite(&pixel, sizeof(unsigned char), 1, newBmp);
    }

    fclose(bmp);
    fclose(newBmp);
    fclose(data);

    printf("Data hiding complete.\n");
    return 0;
}

/**
 * Extracts data from a BMP file using LSB steganography.
 */
int extract_data(const char *stego_bmp, const char *output_data_file) {
    FILE *bmp = fopen(stego_bmp, "rb");
    FILE *outData = fopen(output_data_file, "wb");

    if (!bmp || !outData) {
        fprintf(stderr, "Error opening files.\n");
        return 1;
    }

    // Skip BMP header
    fseek(bmp, BMP_HEADER_SIZE, SEEK_SET);

    unsigned char pixel;
    char extractedChar = 0;
    int bitIndex = 0;

    printf("Extracted message: ");
    while (fread(&pixel, sizeof(unsigned char), 1, bmp)) {
        extractedChar |= (pixel & 1) << bitIndex;
        bitIndex++;

        if (bitIndex == 8) {
            fwrite(&extractedChar, sizeof(char), 1, outData);
            if (extractedChar == '\0') break; // Stop at NULL terminator
            printf("%c", extractedChar);
            bitIndex = 0;
            extractedChar = 0;
        }
    }
    printf("\n");

    fclose(bmp);
    fclose(outData);

    printf("Data extraction complete.\n");
    return 0;
}

