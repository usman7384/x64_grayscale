#include <iostream>
#include <fstream>
#include "CImg.h"

using namespace cimg_library;
using namespace std;

unsigned char *get_pixel_data(CImg<unsigned char> img, int totalPixels)
{
    unsigned char *pixelData = new unsigned char[totalPixels];

    int index = 0;

    for (int i = 0; i < img.height(); i++)
    {
        for (int j = 0; j < img.width(); j++)
        {
            for (int c = 0; c < img.spectrum(); c++)
            {
                pixelData[index++] = img(j, i, 0, c);
            }
        }
    }
    return pixelData;
}

void printImageArray(int height, int width, int channels, unsigned char *imageArray)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            cout << "Pixel (" << x << ", " << y << "): ";
            for (int c = 0; c < channels; c++)
            {
                int index = (y * width + x) * channels + c;
                cout << static_cast<int>(imageArray[index]) << " ";
            }
            cout << endl;
        }
    }
    return;
}

unsigned char *three_to_one_channel(int width, int height, unsigned char *greyScaleData)
{
    int totalPixels = width * height;
    int index = 0;
    int offset = 0;

    unsigned char *final_data = new unsigned char[totalPixels];

    while (index < totalPixels)
    {
        final_data[index] = greyScaleData[offset];
        index++;
        offset = offset + 3;
    }
    return final_data;
}

void saveImage(const std::string &path, const std::string &imageName, unsigned char *imgData, int width, int height, int channels = 1)
{
    CImg<unsigned char> image(imgData, width, height, 1, channels);

    string outputFilename = "output_" + imageName;

    string outputPath = path + outputFilename;
    image.save(outputPath.c_str());

    cout << "Image saved successfully: " << outputPath << endl;
}

void getImageDetails(const CImg<unsigned char> &img, int &width, int &height, int &totalPixels, int &channels)
{
    width = img.width();
    height = img.height();
    channels = img.spectrum();
    totalPixels = width * height * channels;
}

CImg<unsigned char> load_image(const string &path, const string &imageName)
{
    string fullPath = path + imageName;
    ifstream file(fullPath);
    if (file.good())
    {
        CImg<unsigned char> img(fullPath.c_str());
        return img;
    }else{
        throw runtime_error("Failed to load image " + imageName);
    }
    
}
