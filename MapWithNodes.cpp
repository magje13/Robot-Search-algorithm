#include "Header.h"

Mat Mapnodes(Mat& img, vector<Point>& Nodes)
{
	Mat map = img.clone();

	for (int k = 0; k < Nodes.size(); k++)
	{
		int x = Nodes.at(k).x;
		int y = Nodes.at(k).y;
		map.at<Vec3b>(x, y)[0] = 255;
		map.at<Vec3b>(x, y)[1] = 0;
		map.at<Vec3b>(x, y)[2] = 0;
	}

	map.at<Vec3b>(10, 10)[0] = 255;
	map.at<Vec3b>(10, 10)[1] = 0;
	map.at<Vec3b>(10, 10)[2] = 0;
	imwrite("Mapnodes.png", map);
	return map;
}