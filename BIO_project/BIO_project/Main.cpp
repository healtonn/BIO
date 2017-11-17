#include "main.h"

Mat inputImage;
int main(int argc, char** argv)
{

	if (argc != 2)
	{
		cout << " Usage: display_image ImageToLoadAndDisplay" << endl;
		return -1;
	}
	
	inputImage = imread(argv[1], IMREAD_COLOR); // Read the file
	if (inputImage.empty()) // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Display window", inputImage); // Show our image inside it.
	waitKey(0); // Wait for a keystroke in the window

	Mat modifiedImage = inputImage.clone();

	modifiedImage = getGreenChannel(modifiedImage);
	imshow("Display window1", modifiedImage); // Show our image inside it.
	waitKey(0); // Wait for a keystroke in the window

	modifiedImage = modifySaturation(modifiedImage, 2.5, 0);
	imshow("Display window1", modifiedImage); // Show our image inside it.
	waitKey(0); // Wait for a keystroke in the window
	
	Mat greyscale = Mat::zeros(modifiedImage.size(), CV_8UC1);
	for (int y = 0; y < modifiedImage.rows; y++) {
		for (int x = 0; x < modifiedImage.cols; x++) {
			greyscale.at<uchar>(y, x) = modifiedImage.at<Vec3b>(y, x)[0] * 0.11 + modifiedImage.at<Vec3b>(y, x)[1] * 0.59 + modifiedImage.at<Vec3b>(y, x)[2] * 0.3;
		}
	}

	imshow("Display window1", greyscale); // Show our image inside it.
	waitKey(0); // Wait for a keystroke in the window

	greyscale = blurFilter(greyscale, KERNEL_X_SIZE, KERNEL_Y_SIZE);
	imshow("Display window1", greyscale); // Show our image inside it.
	waitKey(0); // Wait for a keystroke in the window
	return 0;
}

Mat modifySaturation(Mat inputImage, float alpha, int beta) {
	Mat resultImage = Mat::zeros(inputImage.size(), inputImage.type());

	for (int y = 0; y < inputImage.rows; y++) {
		for (int x = 0; x < inputImage.cols; x++) {
			for (int c = 0; c < 3; c++) {
				resultImage.at<Vec3b>(y, x)[c] =
					saturate_cast<uchar>(alpha*(inputImage.at<Vec3b>(y, x)[c]) + beta);
			}
		}
	}

	return resultImage;
}

Mat medianFilter(Mat inputImage) {
	Mat resultImage;
	medianBlur(inputImage, resultImage, 3);
	return resultImage;
}

Mat blurFilter(Mat inputImage, int kernelSizeX, int kernelSizeY) {
	Mat resultImage;
	blur(inputImage, resultImage, Size(kernelSizeX, kernelSizeY), Point(-1, -1));
	return resultImage;
}

Mat getGreenChannel(Mat inputImage) {
	Mat resultImage = inputImage.clone();
	for (int y = 0; y < resultImage.rows; y++) {
		for (int x = 0; x < resultImage.cols; x++) {
			resultImage.at<Vec3b>(y, x)[0] = 0;
			resultImage.at<Vec3b>(y, x)[2] = 0;
		}
	}

	return resultImage;
}
