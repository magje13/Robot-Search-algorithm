#include "Header.h"

Mat Voronoi(Mat& img)
{
	int row = img.rows;
	int col = img.cols;
	Mat Vor = img.clone();
	Mat compare = img.clone();

	for (int x = 1; x < col - 1; x++) //Gennemgår billedets x-koordinater
	{
		for (int y = 1; y < row - 1; y++) //Gennemgår billedets y-koordinater
		{
			if (img.at<uint8_t>(Point(x, y)) < 30)
			{
				continue; //Den skal ikke gøre noget så 
			}
			else
			{
				int countb(0); //Hvor mange omkring er større
				int counte(0); //Hvor mange omkring er ens
				for (int i = -1; i < 2; i++) //Dynamisk maske
				{
					for (int j = -1; j < 2; j++)
					{

						if (i == 0 && j == 0) //Tjek ikke det punkt man står på
						{
							continue;
						}
						else if (compare.at<uint8_t>(Point(x, y)) > compare.at<uint8_t>(Point(x + i, y + j))) //Hvis midten er større end dem ved siden af
						{
							countb++;
						}
						else if (compare.at<uint8_t>(Point(x, y)) == img.at<uint8_t>(Point(x + i, y + j))) // Hvis midten har samme størrelse som dem ved siden af
						{
							counte++;
						}
						if (countb > 3 || counte > 4) //I de to tilfælde, skal punktet være en del af en linje
						{
							Vor.at<uint8_t>(Point(x, y)) = 255;
						}
						else
						{
							Vor.at<uint8_t>(Point(x, y)) = 0;
						}

					}

				}
			}
		}
	}


	return Vor;
}



Mat Nodes(Mat& img, vector<Point> &Nodes)
{
	Mat node = img.clone();
	Mat test = img.clone();
	cvtColor(test, test, COLOR_GRAY2BGR);
	
	for (int x = 1; x < node.cols - 1; x++)
	{
		for (int y = 1; y < node.rows - 1; y++)
		{
				//Heller tælles hvor mange hvide pixels der er rundt om det givne pixel. 
			int white = 0;
			for (int i = -1; i < 2; i++)
			{
				for (int j = -1; j < 2; j++)
				{
					if (node.at<uint8_t>(Point(x+i, y+j)) == 255)
					{
						white++;
					}
				}
			}

			if (white == 2)
			{
					//Case 1
				if (node.at<uint8_t>(Point(x, y)) == 255 && node.at<uint8_t>(Point(x - 1, y - 1)) == 255)
				{
					Nodes.push_back(Point(y, x));
					test.at<Vec3b>(y, x)[0] = 255;
					test.at<Vec3b>(y, x)[1] = 0;
					test.at<Vec3b>(y, x)[2] = 0;
				}
					//Case 2
				else if (node.at<uint8_t>(Point(x, y)) == 255 && node.at<uint8_t>(Point(x - 1, y + 1)) == 255)
				{
					Nodes.push_back(Point(y, x));
					test.at<Vec3b>(y, x)[0] = 255;
					test.at<Vec3b>(y, x)[1] = 0;
					test.at<Vec3b>(y, x)[2] = 0;
				}
					//Case 3
				else if (node.at<uint8_t>(Point(x, y)) == 255 && node.at<uint8_t>(Point(x + 1, y - 1)) == 255)
				{
					Nodes.push_back(Point(y, x));
					test.at<Vec3b>(y, x)[0] = 255;
					test.at<Vec3b>(y, x)[1] = 0;
					test.at<Vec3b>(y, x)[2] = 0;
				}
					//Case 4
				else if (node.at<uint8_t>(Point(x, y)) == 255 && node.at<uint8_t>(Point(x + 1, y + 1)) == 255)
				{
					Nodes.push_back(Point(y, x));
					test.at<Vec3b>(y, x)[0] = 255;
					test.at<Vec3b>(y, x)[1] = 0;
					test.at<Vec3b>(y, x)[2] = 0;
				}
					//Case 5
				else if (node.at<uint8_t>(Point(x, y)) == 255 && node.at<uint8_t>(Point(x + 1, y)) == 255)
				{
					Nodes.push_back(Point(y, x));
					test.at<Vec3b>(y, x)[0] = 255;
					test.at<Vec3b>(y, x)[1] = 0;
					test.at<Vec3b>(y, x)[2] = 0;
				}
			}

			if (white == 3)
			{
					//Case 1 
				if (node.at<uint8_t>(Point(x, y)) == 255 && node.at<uint8_t>(Point(x + 1, y)) == 255 && node.at<uint8_t>(Point(x - 1, y - 1)) == 255)
				{
					Nodes.push_back(Point(y, x));
					test.at<Vec3b>(y, x)[0] = 255;
					test.at<Vec3b>(y, x)[1] = 0;
					test.at<Vec3b>(y, x)[2] = 0;
				}
					//Case 2
				else if (node.at<uint8_t>(Point(x, y)) == 255 && node.at<uint8_t>(Point(x, y - 1)) == 255 && node.at<uint8_t>(Point(x + 1, y + 1)) == 255)
				{
					Nodes.push_back(Point(y, x));
					test.at<Vec3b>(y, x)[0] = 255;
					test.at<Vec3b>(y, x)[1] = 0;
					test.at<Vec3b>(y, x)[2] = 0;
				}
					//Case 3
				else if (node.at<uint8_t>(Point(x, y)) == 255 && node.at<uint8_t>(Point(x - 1, y)) == 255 && node.at<uint8_t>(Point(x + 1, y - 1)) == 255)
				{
					Nodes.push_back(Point(y, x));
					test.at<Vec3b>(y, x)[0] = 255;
					test.at<Vec3b>(y, x)[1] = 0;
					test.at<Vec3b>(y, x)[2] = 0;
				}
					//Case 4
				else if (node.at<uint8_t>(Point(x, y)) == 255 && node.at<uint8_t>(Point(x - 1, y)) == 255 && node.at<uint8_t>(Point(x + 1, y + 1)) == 255)
				{
					Nodes.push_back(Point(y, x));
					test.at<Vec3b>(y, x)[0] = 255;
					test.at<Vec3b>(y, x)[1] = 0;
					test.at<Vec3b>(y, x)[2] = 0;
				}
					//Case 5
				else if (node.at<uint8_t>(Point(x, y)) == 255 && node.at<uint8_t>(Point(x - 1, y - 1)) == 255 && node.at<uint8_t>(Point(x, y + 1)) == 255)
				{
					Nodes.push_back(Point(y, x));
					test.at<Vec3b>(y, x)[0] = 255;
					test.at<Vec3b>(y, x)[1] = 0;
					test.at<Vec3b>(y, x)[2] = 0;
				}
					//Case 6
				else if (node.at<uint8_t>(Point(x, y)) == 255 && node.at<uint8_t>(Point(x, y - 1)) == 255 && node.at<uint8_t>(Point(x - 1, y + 1)) == 255)
				{
					Nodes.push_back(Point(y, x));
					test.at<Vec3b>(y, x)[0] = 255;
					test.at<Vec3b>(y, x)[1] = 0;
					test.at<Vec3b>(y, x)[2] = 0;
				}
			}

			if (white == 4)
			{
					//Case 1
				if (node.at<uint8_t>(Point(x, y)) == 255 && node.at<uint8_t>(Point(x - 1, y - 1)) == 255 && node.at<uint8_t>(Point(x - 1, y + 1)) == 255 && node.at<uint8_t>(Point(x + 1, y)) == 255)
				{
					Nodes.push_back(Point(y, x));
					test.at<Vec3b>(y, x)[0] = 255;
					test.at<Vec3b>(y, x)[1] = 0;
					test.at<Vec3b>(y, x)[2] = 0;
				}
					//Case 2
				else if (node.at<uint8_t>(Point(x, y)) == 255 && node.at<uint8_t>(Point(x - 1, y)) == 255 && node.at<uint8_t>(Point(x + 1, y + 1)) == 255 && node.at<uint8_t>(Point(x + 1, y - 1)) == 255)
				{
					Nodes.push_back(Point(y, x));
					test.at<Vec3b>(y, x)[0] = 255;
					test.at<Vec3b>(y, x)[1] = 0;
					test.at<Vec3b>(y, x)[2] = 0;
				}
					//Case 3
				else if (node.at<uint8_t>(Point(x, y)) == 255 && node.at<uint8_t>(Point(x, y + 1)) == 255 && node.at<uint8_t>(Point(x - 1, y - 1)) == 255 && node.at<uint8_t>(Point(x + 1, y - 1)) == 255)
				{
					Nodes.push_back(Point(y, x));
					test.at<Vec3b>(y, x)[0] = 255;
					test.at<Vec3b>(y, x)[1] = 0;
					test.at<Vec3b>(y, x)[2] = 0;
				}
					//Case 4
				else if (node.at<uint8_t>(Point(x, y)) == 255 && node.at<uint8_t>(Point(x, y - 1)) == 255 && node.at<uint8_t>(Point(x - 1, y)) == 255 && node.at<uint8_t>(Point(x - 1, y + 1)) == 255)
				{
					Nodes.push_back(Point(y, x));
					test.at<Vec3b>(y, x)[0] = 255;
					test.at<Vec3b>(y, x)[1] = 0;
					test.at<Vec3b>(y, x)[2] = 0;
				}
					//Case 5
				else if (node.at<uint8_t>(Point(x, y)) == 255 && node.at<uint8_t>(Point(x - 1, y + 1)) == 255 && node.at<uint8_t>(Point(x + 1, y)) == 255 && node.at<uint8_t>(Point(x + 1, y - 1)) == 255)
				{
					Nodes.push_back(Point(y, x));
					test.at<Vec3b>(y, x)[0] = 255;
					test.at<Vec3b>(y, x)[1] = 0;
					test.at<Vec3b>(y, x)[2] = 0;
				}
				
			}

			if (white == 5)
			{
					//Case 1
				if (node.at<uint8_t>(Point(x, y)) == 255 && node.at<uint8_t>(Point(x - 1, y - 1)) == 255 && node.at<uint8_t>(Point(x + 1, y)) == 255 
					&& node.at<uint8_t>(Point(x , y + 1)) == 255 && node.at<uint8_t>(Point(x + 1, y + 1)) == 255)
				{
				Nodes.push_back(Point(y, x));
				test.at<Vec3b>(y, x)[0] = 255;
				test.at<Vec3b>(y, x)[1] = 0;
				test.at<Vec3b>(y, x)[2] = 0;
				}
					//Case 2
				else if (node.at<uint8_t>(Point(x, y)) == 255 && node.at<uint8_t>(Point(x + 1, y + 1)) == 255 && node.at<uint8_t>(Point(x - 1, y)) == 255
					&& node.at<uint8_t>(Point(x - 1, y - 1)) == 255 && node.at<uint8_t>(Point(x, y - 1)) == 255)
				{
					Nodes.push_back(Point(y, x));
					test.at<Vec3b>(y, x)[0] = 255;
					test.at<Vec3b>(y, x)[1] = 0;
					test.at<Vec3b>(y, x)[2] = 0;
				}
			}

		}
	}

	//vector<int> compression_params;
	//compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	//compression_params.push_back(9);

	//imwrite("Nodes.png", test, compression_params);
	//imshow("voronoi", img);
	
	return test;
}