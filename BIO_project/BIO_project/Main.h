#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"


using namespace cv;
using namespace std;

#define BLUR_KERNEL_SIZE 5

Mat inputImage;

/*
Apply gaussian blur.
@param filterArea - sizeX a sizeY must be ODD and >0 (greater than zero).
*/
Mat gaussianSmoothing(Mat bgrImage, Size filterArea, int sigmaX, int sigmaY);

/*
Modify saturation of BGR or Grayscale image format.
*/
Mat modifySaturation(Mat inputImage, float alpha, int beta);

/*
Blur image using median filter method.
*/
Mat medianFilter(Mat inputImage);

/*
Blur image base on kernel size.
*/
Mat blurFilter(Mat inputImage, int kernelSizeX, int kernelSizeY);

/*
For BGR image set Blue and Red values to zero, so only Green channel remains.
*/
Mat getGreenChannel(Mat inputImage);

/*Transform BGR*/
Mat weightedGrayscale(Mat inputImage);

/*
Convert BGR image to Grayscale image based on GREEN channel values ONLY!
Green channel can be weighted if needed.
*/
Mat weightedGrayscale(Mat inputImage, float weight);

/*
Dilate grayscale image.
*/
Mat dilate(Mat inputImage, int iterations);

/*
Erode grayscale image.
*/
Mat erode(Mat inputImage, int iterations);

/*
Contrast Limited Adaptive Histogram Equalization.
Makes retinal image more balanced if some places are dark because of bad scanning.
Also makes aneurysms more visible and contrasting with their surroundings.
*/
Mat equalizeCLAHE(Mat bgrImage, int clip, Size areaGridSize);

/*
High pass filter for image (apply to Fourier's coeficients).
*/
Mat getHighPassFilter(Mat fourierCoefs, float sigma);

/*
Count standard deviation in 1-channel array.
*/
float getStandardDeviation(Mat srcArray);

/*
Count discrete fourier transformation for grayscale image.
Returns discrete fourier coeficients.
*/
Mat discreteFourier2D(Mat greyscaleImage);