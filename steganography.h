#ifndef STEGANOGRAPHY_H
#define STEGANOGRAPHY_H

int embed_data(const char *input_bmp, const char *output_bmp, const char *data_file);
int extract_data(const char *stego_bmp, const char *output_data_file);

#endif

