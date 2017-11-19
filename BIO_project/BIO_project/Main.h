#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"


using namespace cv;
using namespace std;

#define BLUR_KERNEL_SIZE 5

Mat inputImage;

Mat gaussianSmoothing(Mat bgrImage, Size filterArea, int sigmaX, int sigmaY);

Mat modifySaturation(Mat inputImage, float alpha, int beta);

Mat medianFilter(Mat inputImage);

Mat blurFilter(Mat inputImage, int kernelSizeX, int kernelSizeY);

Mat getGreenChannel(Mat inputImage);

Mat weightedGrayscale(Mat inputImage);

Mat weightedGrayscale(Mat inputImage, float weight);

Mat dilate(Mat inputImage, int iterations);

Mat erode(Mat inputImage, int iterations);

Mat equalizeCLAHE(Mat bgrImage, int clip, Size areaGridSize);

/*
opencv_highgui2413.lib
opencv_highgui2413d.lib
opencv_imgproc2413.lib
opencv_imgproc2413d.lib
opencv_features2d2413.lib
opencv_features2d2413d.lib
opencv_core2413.lib
opencv_core2413d.lib
*/