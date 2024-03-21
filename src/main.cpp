#include <iostream>
#include <fstream>
#include <vector>
#include "Picture.h"
#include <algorithm>
using namespace std;

Picture Read(const string& filename, Picture::Header& header) {
    Pixel pixel;
    Picture InputtedFile;
    ifstream File(filename, ios::binary);
    if (!File) {
        cerr << "Error: Not able to open the input file." << endl;
        // return 1;
    }
    File.read((char*) &header.idLength, sizeof(header.idLength));
    File.read((char*) &header.colorMapType, sizeof(header.colorMapType));
    File.read((char*) &header.dataTypeCode, sizeof(header.dataTypeCode));
    File.read((char*) &header.colorMapOrigin, sizeof(header.colorMapOrigin));
    File.read((char*) &header.colorMapLength, sizeof(header.colorMapLength));
    File.read((char*) &header.colorMapDepth, sizeof(header.colorMapDepth));
    File.read((char*) &header.xOrigin, sizeof(header.xOrigin));
    File.read((char*) &header.yOrigin, sizeof(header.yOrigin));
    File.read((char*) &header.width, sizeof(header.width));
    File.read((char*) &header.height, sizeof(header.height));
    File.read((char*) &header.bitsPerPixel, sizeof(header.bitsPerPixel));
    File.read((char*) &header.imageDescriptor, sizeof(header.imageDescriptor));
    for (int i = 0; i < header.width * header.height; i++) {
        File.read((char*) &pixel.blue, sizeof(pixel.blue));
        File.read((char*) &pixel.green, sizeof(pixel.green));;
        File.read((char*) &pixel.red, sizeof(pixel.red));
        InputtedFile.pixels.push_back(pixel);
    }
    return InputtedFile;
}

void Write(const string& filename, Picture::Header& header, Picture& resultImage) {
    // writing to a new TGA file
    fstream File(filename, ios_base::out | ios_base::binary);
    // writing the header
    File.write(reinterpret_cast<char*>(&header.idLength), sizeof(header.idLength));
    File.write(reinterpret_cast<char*>(&header.colorMapType), sizeof(header.colorMapType));
    File.write(reinterpret_cast<char*>(&header.dataTypeCode), sizeof(header.dataTypeCode));
    File.write(reinterpret_cast<char*>(&header.colorMapOrigin), sizeof(header.colorMapOrigin));
    File.write(reinterpret_cast<char*>(&header.colorMapLength), sizeof(header.colorMapLength));
    File.write(reinterpret_cast<char*>(&header.colorMapDepth), sizeof(header.colorMapDepth));
    File.write(reinterpret_cast<char*>(&header.xOrigin), sizeof(header.xOrigin));
    File.write(reinterpret_cast<char*>(&header.yOrigin), sizeof(header.yOrigin));
    File.write(reinterpret_cast<char*>(&header.width), sizeof(header.width));
    File.write(reinterpret_cast<char*>(&header.height), sizeof(header.height));
    File.write(reinterpret_cast<char*>(&header.bitsPerPixel), sizeof(header.bitsPerPixel));
    File.write(reinterpret_cast<char*>(&header.imageDescriptor), sizeof(header.imageDescriptor));
    for (int i = 0; i < header.width * header.height; i++) {
        File.write(reinterpret_cast<char *>(&resultImage.pixels[i].blue), sizeof(resultImage.pixels[i].blue));
        File.write(reinterpret_cast<char *>(&resultImage.pixels[i].green), sizeof(resultImage.pixels[i].green));
        File.write(reinterpret_cast<char *>(&resultImage.pixels[i].red), sizeof(resultImage.pixels[i].red));
    }
    File.close();
}

int main() {
 // Task 1:
    Picture::Header header1{};
    Picture Image1 = Read("input/layer1.tga", header1);
    Picture Image2 = Read("input/pattern1.tga", header1);
    Picture resultP1 = Image1.Multiply(Image2);
    Write("output/part1.tga", header1, resultP1);

// Task 2:

    Picture::Header headerCar, headerLayer2;
    Picture carImage = Read("input/car.tga", headerCar);
    Picture layer2Image = Read("input/layer2.tga", headerLayer2);
    Picture resultImage = carImage.Subtract(layer2Image);
    Write("output/part2.tga", headerCar, resultImage);  // Assuming we want to keep the header from car.tga


// Task 3:
    Picture::Header headerLayer1, headerPattern2, headerText;
    Picture layer1Image = Read("input/layer1.tga", headerLayer1);
    Picture pattern2Image = Read("input/pattern2.tga", headerPattern2);
    Picture textImage = Read("input/text.tga", headerText);
    Picture tempMultiplyResult = layer1Image.Multiply(pattern2Image);
    Picture finalResult = tempMultiplyResult.Screen(textImage);
    Write("output/task3_result.tga", headerLayer1, finalResult);


// Task 4:
    Picture::Header headerLayer2_T4, headerCircles, headerPattern2_T4; // Renamed variables to avoid redefinition
    Picture layer2Image_T4 = Read("input/layer2.tga", headerLayer2_T4);
    Picture circlesImage = Read("input/circles.tga", headerCircles);
    Picture pattern2Image_T4 = Read("input/pattern2.tga", headerPattern2_T4);
    Picture multiplyResultT4 = layer2Image_T4.Multiply(circlesImage);
    Picture finalResultT4 = multiplyResultT4.Subtract(pattern2Image_T4);
    Write("output/part4.tga", headerLayer2_T4, finalResultT4);


// Task 5:
    Picture::Header headerLayer, headerPattern1;
    Picture layer1Image1 = Read("input/layer1.tga", headerLayer);
    Picture pattern1Image = Read("input/pattern1.tga", headerPattern1);
    Picture overlayResult = layer1Image1.Overlay(pattern1Image);
    Write("output/part5.tga", headerLayer, overlayResult);


// Task 6:
    Picture::Header headerCar2;
    Picture carImage2 = Read("input/car.tga", headerCar2);

    for (Pixel& pixel : carImage2.pixels) {
        int greenValue = pixel.green + 200;  // Add 200 to green channel
        pixel.green = (greenValue > 255) ? 255 : static_cast<unsigned char>(greenValue);  // Clamp to 255 if it goes over
    }

    Write("output/part6.tga", headerCar2, carImage2);  // Write the updated car image


// Task 7:
    Picture::Header headerCar3;
    Picture carImage3 = Read("input/car.tga", headerCar3);
    for (Pixel& pixel : carImage.pixels) {
        // Multiply red by 4, ensure it does not exceed the max value of 255
        int redValue = pixel.red * 4;
        pixel.red = (redValue > 255) ? 255 : static_cast<unsigned char>(redValue);

        // Set blue to 0
        pixel.blue = 0;
    }
    Write("output/part7.tga", headerCar, carImage);  // Write the updated car image


// Task 8:
    Picture::Header headerCar4;
    Picture carImage4 = Read("input/car.tga", headerCar4);

    Picture redChannelImage = carImage4;
    Picture greenChannelImage = carImage4;
    Picture blueChannelImage = carImage4;

    for (size_t i = 0; i < carImage4.pixels.size(); ++i) {
        // Create red channel image (grayscale image with red channel intensity)
        redChannelImage.pixels[i].green = carImage4.pixels[i].red;
        redChannelImage.pixels[i].blue = carImage4.pixels[i].red;

        // Create green channel image (grayscale image with green channel intensity)
        greenChannelImage.pixels[i].red = carImage4.pixels[i].green;
        greenChannelImage.pixels[i].blue = carImage4.pixels[i].green;

        // Create blue channel image (grayscale image with blue channel intensity)
        blueChannelImage.pixels[i].red = carImage4.pixels[i].blue;
        blueChannelImage.pixels[i].green = carImage4.pixels[i].blue;
    }

    Write("output/part8_r.tga", headerCar4, redChannelImage);
    Write("output/part8_g.tga", headerCar4, greenChannelImage);
    Write("output/part8_b.tga", headerCar4, blueChannelImage);


// Task 9:
    Picture::Header headerRed, headerGreen, headerBlue;
    Picture layerRedImage = Read("input/layer_red.tga", headerRed);
    Picture layerGreenImage = Read("input/layer_green.tga", headerGreen);
    Picture layerBlueImage = Read("input/layer_blue.tga", headerBlue);

// Assuming all three images have the same dimensions
    Picture combinedImage;
    combinedImage.pixels.resize(layerRedImage.pixels.size());

    for (size_t i = 0; i < combinedImage.pixels.size(); ++i) {
        combinedImage.pixels[i].red = layerRedImage.pixels[i].red;
        combinedImage.pixels[i].green = layerGreenImage.pixels[i].green;
        combinedImage.pixels[i].blue = layerBlueImage.pixels[i].blue;
    }

    Write("output/combined_image.tga", headerRed, combinedImage); // Use any header since all should be the same

// Task 10:
    Picture::Header headerText2;
    Picture text2Image = Read("input/text2.tga", headerText2);

// To rotate 180 degrees, reverse the pixel array
    reverse(text2Image.pixels.begin(), text2Image.pixels.end());

    Write("output/text2_rotated.tga", headerText2, text2Image);


    return 0;
}
