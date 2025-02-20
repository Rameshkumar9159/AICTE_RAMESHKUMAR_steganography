Secure Data Hiding in Images Using Steganography

This project demonstrates a simple implementation of steganography in C, allowing you to hide and extract data within BMP images.
Files

    main.c: The main driver program.
    steganography.h: Header file containing function declarations.
    steganography.c: Source file containing the implementation of steganography functions.
    Makefile: Script to build the project.

Usage
Building the Project

To compile the project, run:

make

Embedding Data

To embed data into an image:

./steganography embed <input_bmp> <output_bmp> <data_file>

Extracting Data

To extract hidden data from an image:

./steganography extract <stego_bmp> <output_data_file>
All about detailed in README.docx  

