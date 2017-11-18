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

Mat modifySaturation(Mat inputImage, float alpha, int beta);

Mat medianFilter(Mat inputImage);

Mat blurFilter(Mat inputImage, int kernelSizeX, int kernelSizeY);

Mat getGreenChannel(Mat inputImage);

Mat weightedGrayscale(Mat inputImage);

Mat dilate(Mat inputImage, int iterations);

Mat erode(Mat inputImage, int iterations);

Mat equalizeCLAHE(Mat bgrImage, int clip, Size areaGridSize);