#ifndef PROJECT2_PICTURE_H
#define PROJECT2_PICTURE_H

#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>

using namespace std;

struct Pixel {
    unsigned char blue;
    unsigned char green;
    unsigned char red;

    // Constructors
    Pixel() : blue(0), green(0), red(0) {}
    Pixel(unsigned char b, unsigned char g, unsigned char r) : blue(b), green(g), red(r) {}
};


struct Picture {
    struct Header {
        char idLength;
        char colorMapType;
        char dataTypeCode;
        short colorMapOrigin;
        short colorMapLength;
        char colorMapDepth;
        short xOrigin;
        short yOrigin;
        short width;
        short height;
        char bitsPerPixel;
        char imageDescriptor;
    };

    std::vector<Pixel> pixels;

    Picture Multiply(const Picture &otherImage);

    Picture Overlay(const Picture &otherImage);

    Picture Subtract(const Picture &otherImage);

    Picture Screen(const Picture &otherImage);
};



#endif //PROJECT2_PICTURE_H
