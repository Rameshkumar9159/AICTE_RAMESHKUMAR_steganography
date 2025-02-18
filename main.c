#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "steganography.h"

void print_usage(char *program_name) {
    printf("Usage:\n");
    printf("  %s embed <input_bmp> <output_bmp> <data_file>\n", program_name);
    printf("  %s extract <stego_bmp> <output_data_file>\n", program_name);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "embed") == 0) {
        if (argc != 5) {
            print_usage(argv[0]);
            return 1;
        }
        if (embed_data(argv[2], argv[3], argv[4]) != 0) {
            fprintf(stderr, "Failed to embed data.\n");
            return 1;
        }
        printf("Data embedded successfully.\n");
    } else if (strcmp(argv[1], "extract") == 0) {
        if (argc != 4) {
            print_usage(argv[0]);
            return 1;
        }
        if (extract_data(argv[2], argv[3]) != 0) {
            fprintf(stderr, "Failed to extract data.\n");
            return 1;
        }
        printf("Data extracted successfully.\n");
    } else {
        print_usage(argv[0]);
        return 1;
    }

    return 0;
}

