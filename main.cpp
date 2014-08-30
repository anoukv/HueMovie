#include <iostream>
#include <opencv2/opencv.hpp>

// Loads and displays an image
int main(int argc, const char * argv[])
{
    if(argc < 2)
    {
        std::cout << "Usage: <PATH TO IMAGE>\n";
        return -1;
    }
    
    // read and resize image
    std::string filename = argv[1];
    cv::Mat image = cv::imread(filename);    
    cv::resize(image, image, cv::Size(image.cols / 25, image.rows / 25));


    // initialize counters
    int avgBlue = 0;
    int avgGreen = 0;
    int avgRed = 0;
    int counter = 0;

    int btemp, gtemp, rtemp;

    // for every pixel in the image
    for(int i = 0; i < image.rows; i++)
    {
        for(int j = 0; j < image.cols; j++)
        {
            // get the color of the pixels
            cv::Vec3b color = image.at<cv::Vec3b>(i, j);
            btemp = (int) color[0];
            gtemp = (int) color[1];
            rtemp = (int) color[2];

            // if the color is not black
            // add it to the averages
            if (btemp != 0 && gtemp != 0 && rtemp != 0)
            {
                counter++;
                avgBlue += btemp;
                avgGreen += gtemp;
                avgRed += rtemp;
            }
        }
    }
    
    // acutally average
    float b = (float) avgBlue / counter;
    float g = (float) avgGreen / counter;
    float r = (float) avgRed / counter;

    // write color to out
    std::cout << b << " " <<  g << " " << r << "\n";

    return 0;
}

