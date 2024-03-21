#include "Picture.h"

// Helper function to normalize pixel values to [0, 1]
inline float Normalize(unsigned char value) {
    return value / 255.0f;
}

// Helper function to denormalize pixel values back to [0, 255]
inline unsigned char Denormalize(float value) {
    return static_cast<unsigned char>(value * 255.0f);
}

Pixel MultiplyPixel(const Pixel &p1, const Pixel &p2) {
    return Pixel(
            Denormalize(Normalize(p1.blue) * Normalize(p2.blue)),
            Denormalize(Normalize(p1.green) * Normalize(p2.green)),
            Denormalize(Normalize(p1.red) * Normalize(p2.red))
    );
}

Pixel ScreenPixel(const Pixel &p1, const Pixel &p2) {
    return Pixel(
            Denormalize(1 - (1 - Normalize(p1.blue)) * (1 - Normalize(p2.blue))),
            Denormalize(1 - (1 - Normalize(p1.green)) * (1 - Normalize(p2.green))),
            Denormalize(1 - (1 - Normalize(p1.red)) * (1 - Normalize(p2.red)))
    );
}

Pixel SubtractPixel(const Pixel &p1, const Pixel &p2) {
    return Pixel(
            max(0, p1.blue - p2.blue),
            max(0, p1.green - p2.green),
            max(0, p1.red - p2.red)
    );
}

Pixel OverlayPixel(const Pixel &p1, const Pixel &p2) {
    float blue = Normalize(p2.blue) <= 0.5 ? 2 * Normalize(p1.blue) * Normalize(p2.blue) : 1 - 2 * (1 - Normalize(p1.blue)) * (1 - Normalize(p2.blue));
    float green = Normalize(p2.green) <= 0.5 ? 2 * Normalize(p1.green) * Normalize(p2.green) : 1 - 2 * (1 - Normalize(p1.green)) * (1 - Normalize(p2.green));
    float red = Normalize(p2.red) <= 0.5 ? 2 * Normalize(p1.red) * Normalize(p2.red) : 1 - 2 * (1 - Normalize(p1.red)) * (1 - Normalize(p2.red));

    return Pixel(
            Denormalize(blue),
            Denormalize(green),
            Denormalize(red)
    );
}

// Then in each Picture method you call the corresponding Pixel function for each pixel
Picture Picture::Multiply(const Picture &otherImage) {
    Picture result;
    result.pixels.resize(this->pixels.size());

    for (size_t i = 0; i < this->pixels.size(); ++i) {
        result.pixels[i] = MultiplyPixel(this->pixels[i], otherImage.pixels[i]);
    }

    return result;
}

Picture Picture::Screen(const Picture &otherImage) {
    Picture result;
    result.pixels.resize(this->pixels.size());

    for (size_t i = 0; i < this->pixels.size(); ++i) {
        result.pixels[i] = ScreenPixel(this->pixels[i], otherImage.pixels[i]);
    }

    return result;
}

Picture Picture::Subtract(const Picture &otherImage) {
    Picture result;
    result.pixels.resize(this->pixels.size());

    for (size_t i = 0; i < this->pixels.size(); ++i) {
        result.pixels[i] = SubtractPixel(this->pixels[i], otherImage.pixels[i]);
    }
    return result;
}

Picture Picture::Overlay(const Picture &otherImage) {
    Picture result;
    result.pixels.resize(this->pixels.size());
    for (size_t i = 0; i < this->pixels.size(); ++i) {
        result.pixels[i] = OverlayPixel(this->pixels[i], otherImage.pixels[i]);
    }

    return result;
}