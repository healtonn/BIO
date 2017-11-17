#pragma once

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"


using namespace cv;
using namespace std;

#define KERNEL_X_SIZE 5
#define KERNEL_Y_SIZE 5

int DELAY_CAPTION = 1500;
int DELAY_BLUR = 100;
int MAX_KERNEL_LENGTH = 31;

Mat modifySaturation(Mat inputImage, float alpha, int beta);

Mat medianFilter(Mat inputImage);

Mat blurFilter(Mat inputImage, int kernelSizeX, int kernelSizeY);

Mat getGreenChannel(Mat inputImage);