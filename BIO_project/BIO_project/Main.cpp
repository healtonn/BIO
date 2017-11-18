#include "main.h"

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

	namedWindow("Display window", WINDOW_AUTOSIZE);
	imshow("Display window", inputImage);
	waitKey(0);

	Mat modifiedImage = equalizeCLAHE(inputImage, 4, Size(7, 7));
	imshow("Display window1", modifiedImage);
	waitKey(0);

	modifiedImage = getGreenChannel(modifiedImage);
	modifiedImage = modifySaturation(modifiedImage, 1.5, 0);
	imshow("Display window1", modifiedImage);
	waitKey(0);
	
	Mat greyscale = weightedGrayscale(modifiedImage);
	Mat tmp = greyscale.clone();
	//GaussianBlur(tmp, greyscale, cv::Size(0, 0), 1);
	//addWeighted(tmp, 1.5, greyscale, -0.5, 10, greyscale);

	int kernelSize = BLUR_KERNEL_SIZE;
	greyscale = blurFilter(greyscale, kernelSize, kernelSize);
	imshow("Display window1", greyscale);
	waitKey(0);

	greyscale = erode(greyscale, 2);
	//greyscale = dilate(greyscale, 5);


	imshow("Display window1", greyscale);
	waitKey(0);

	//double treshold1 = 100;
	//double treshold2 = 10;
	//Canny(greyscale, edges, treshold1, treshold2, 5, true);
	//imshow("Display window2", edges); // Show our image inside it.
	//waitKey(0); // Wait for a keystroke in the window

	SimpleBlobDetector::Params params;

	params.minThreshold = 10;
	params.maxThreshold = 100;

	params.filterByArea = true;
	params.minArea = 70.0f;

	params.filterByCircularity = true;
	params.minCircularity = 0.1f;

	params.filterByConvexity = true;
	params.minConvexity = 0.1f;

	params.filterByInertia = true;
	params.minInertiaRatio = 0.1f;

	SimpleBlobDetector detector(params);
	std::vector<KeyPoint> keypoints;
	detector.detect(greyscale, keypoints);

	drawKeypoints(greyscale, keypoints, greyscale, Scalar(0, 255, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	imshow("Display window2", greyscale);
	waitKey(0);

	drawKeypoints(inputImage, keypoints, inputImage, Scalar(0, 255, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	imshow("Display window1", inputImage);
	waitKey(0); // Wait for a keystroke in the window


	return 0;
}

Mat equalizeCLAHE(Mat bgrImage, int clip, Size areaGridSize) {
	Mat labImage, bgrResult, tmp;
	cvtColor(bgrImage, labImage, CV_BGR2Lab);

	// Extract the L (Lightness, intensity) channel
	vector<Mat> labPlanes(3);
	split(labImage, labPlanes);  // now we have the L image in labPlanes[0]

								 // apply the CLAHE algorithm to the L channel
	Ptr<CLAHE> clahe = createCLAHE();
	clahe->setClipLimit(clip);
	clahe->setTilesGridSize(areaGridSize);
	clahe->apply(labPlanes[0], tmp);
	// Merge the the color planes back into an Lab image
	tmp.copyTo(labPlanes[0]);
	merge(labPlanes, labImage);

	// convert back to RGB
	cvtColor(labImage, bgrResult, CV_Lab2BGR);

	//clear clahe - dont know if needed, but to be sure it is not saved for other usages...
	clahe->collectGarbage();

	return bgrResult;
}

Mat dilate(Mat inputImage, int iterations) {
	int size = 3;
	Mat element = getStructuringElement(MORPH_RECT,
		Size(2 * size + 1, 2 * size + 1),
		Point(size, size));

	Mat resultImage;
	dilate(inputImage, resultImage, 7, Point(-1, -1), iterations);
	return resultImage;
}

Mat erode(Mat inputImage, int iterations) {
	int size = 3;
	Mat element = getStructuringElement(MORPH_RECT,
		Size(2 * size + 1, 2 * size + 1),
		Point(size, size));


	Mat resultImage;
	erode(inputImage, resultImage, element, Point(-1, -1), iterations);
	return resultImage;
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

Mat weightedGrayscale(Mat inputImage) {
	Mat resultImage = Mat::zeros(inputImage.size(), CV_8UC1);

	for (int y = 0; y < inputImage.rows; y++) {
		for (int x = 0; x < inputImage.cols; x++) {
			resultImage.at<uchar>(y, x) = (uchar) (inputImage.at<Vec3b>(y, x)[0] * 0.11 + inputImage.at<Vec3b>(y, x)[1] * 0.59 + inputImage.at<Vec3b>(y, x)[2] * 0.3);
		}
	}

	return resultImage;
}