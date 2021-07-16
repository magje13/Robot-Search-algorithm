#include "Header.h"

Mat editcolor(Mat& img) {
	Mat red = img.clone();
	
	for (int i = 0; i < red.rows; i++) {
		for (int j = 0; j < red.cols; j++) {

			if (red.at<Vec3b>(i, j)[0] > 0)
			{
				red.at<Vec3b>(i, j)[0] = 255;
				red.at<Vec3b>(i, j)[1] = 255;
				red.at<Vec3b>(i, j)[2] = 255;
			}
		}
	}

	cvtColor(red, red, COLOR_BGR2GRAY);
	return red;
}