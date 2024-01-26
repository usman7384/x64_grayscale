#include <iostream>
#include "CImg.h"
#include <string>
#include <exception>
#include "utils.h"

using namespace std;
using namespace cimg_library;

extern "C" unsigned char *rgb_to_greyscale(int height, int width, unsigned char *pixelData);


int main(int argc, char* argv[])
{
    const char *path = "./imgs/";
    const char *filename = argv[1];
    int width, height, totalPixels, channels;
    try
    {
        CImg<unsigned char> img = load_image(path, filename);
        getImageDetails(img, width, height, totalPixels, channels);

        unsigned char *imageData = get_pixel_data(img, totalPixels);

        unsigned char *finalData = three_to_one_channel(width, height, rgb_to_greyscale(height, width, imageData));

        CImg<unsigned char> grayscale_img(finalData, width, height, 1, 1);

        saveImage(path,filename,finalData,width,height,1);

        delete[] imageData;
    }
    catch (const exception &e)
    {
        // Catch the exception and handle the error
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
