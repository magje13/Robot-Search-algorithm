#include "Header.h"


Mat Brushfire(Mat& img) {

	int row = img.rows;
	int col = img.cols;
	Mat copy = img.clone();
	vector<Point> neighbour;

		//Her tjekker vi billedet med en dynamisk maske og finder alle de hvide pixels ved siden af et sort pixel
		//med en dynamisk maske. 

	int color = 1;

	for (int i = 1; i < row - 1; i++) {
		for (int j = 1; j < col - 1; j++) {

			if (img.at<uint8_t>(i, j) == 0) {

				for (int x = i - 1; x <= i + 1; x++) {
					for (int y = j - 1; y <= j + 1; y++) {

						if (img.at<uint8_t>(x, y) == 255 )
						{
							bool foundneighbour = false;

							if (copy.at<uint8_t>(x, y) == color) {
								foundneighbour = true;
							}

							copy.at<uint8_t>(x, y) = color; 
							
							if (!foundneighbour)
								neighbour.push_back(Point(x, y));
							
						}
					}
				}
			}
		}
	}
	

	//Her fortæller vi hvilken farve de hvide pixels skal have og laver en ny vector. 
	
	
	for (int k = 0; k < neighbour.size(); k++)
	{
		int x = neighbour.at(k).x;
		int y = neighbour.at(k).y;
		img.at<uint8_t>(x, y) = color;
	}


	//	Her farver vi alle de hvide felter i vores vecktor "neighbors". 

	while (neighbour.size() != 0)
	{

		vector<Point> newneighbour;

		for (int k = 0; k < neighbour.size(); k++)
		{
			int i = neighbour.at(k).x;
			int j = neighbour.at(k).y;
			
			if (img.at<uint8_t>(i, j) == color) {
				for (int x = i - 1; x <= i + 1; x++) {
					for (int y = j - 1; y <= j + 1; y++) {
						if (img.at<uint8_t>(x, y) == 255)
						{
							bool foundneighbour = false;
							if (img.at<uint8_t>(x, y) == color) {
								foundneighbour = true;
							}
							img.at<uint8_t>(x, y) = color+3;

							if (!foundneighbour)
							{
								newneighbour.push_back(Point(x, y));
							}

						}
					}
				}

			}
		}
		
		neighbour = newneighbour;
		color = color + 3;

	}

	//imshow("BrushFire", img);
	

	return(img);
}

