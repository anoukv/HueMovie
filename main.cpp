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
    
    std::string filename = argv[1];
    // cv::namedWindow("result");
    cv::Mat image = cv::imread(filename);    
    cv::resize(image, image, cv::Size(image.cols / 25, image.rows / 25));
    // cv::imshow("result", image);
    // cv::waitKey(0);

    int avgBlue = 0;
    int avgGreen = 0;
    int avgRed = 0;
    int counter = 0;

    int btemp, gtemp, rtemp;

    for(int i = 0; i < image.rows; i++)
    {
        for(int j = 0; j < image.cols; j++)
        {
            cv::Vec3b color = image.at<cv::Vec3b>(i, j);
            btemp = (int) color[0];
            gtemp = (int) color[1];
            rtemp = (int) color[2];
            if (btemp != 0 && gtemp != 0 && rtemp != 0)
            {
                // std::cout << (int)color[0] << " " << (int)color[1] << " " << (int)color[2] << "\n";
                counter++;
                avgBlue += btemp;
                avgGreen += gtemp;
                avgRed += rtemp;
            }
        }
    }
    
    float b = (float) avgBlue / counter;
    float g = (float) avgGreen / counter;
    float r = (float) avgRed / counter;
    std::cout << b << " " <<  g << " " << r << "\n";

    for(int i = 0; i < image.rows; i++)
    {
        for(int j = 0; j < image.cols; j++)
        {
            image.at<cv::Vec3b>(i, j)[0] = b;
            image.at<cv::Vec3b>(i, j)[1] = g;
            image.at<cv::Vec3b>(i, j)[2] = r;

        }
    }

    // cv::imshow("result", image);
    // cv::waitKey(0);

    return 0;
}

