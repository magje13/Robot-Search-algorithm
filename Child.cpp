#include "Header.h"

vector<vector <Point>> Child(vector<vector <Point>> & parent, vector<Point>& Nodes, Mat& img)
{
		//Dette forloop går igennem vectoren med alle noderne i mappet
	for (int currentindex = 0; currentindex < size(Nodes); currentindex++)
	{
		int x = Nodes.at(currentindex).x;
		int y = Nodes.at(currentindex).y;
		vector<Point> Childnodes;
		vector<Point> temp;
		parent.push_back(temp);
		double distance[58];
		bool con = false;

			//Her bliver hvert punkt evalueret i forhold til punktet vi er placeret i. 
		for (int nextindex = 0; nextindex < size(Nodes); nextindex++)
		{
			if (currentindex != nextindex)
			{
				int x1 = Nodes.at(nextindex).x;
				int y1 = Nodes.at(nextindex).y;

				distance[nextindex] = sqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y));
			}
			else
			{
				distance[currentindex] = 10000;
			}
			
		}

		

		for (int numpix = 0; numpix < 9; numpix++)
		{
			int min = 1000;
			int index = 0;
			for (int i = 0; i < size(distance); i++)
			{
				// Jeg skal tjekke alle distance igennem for at finde minimum
				// Når jeg har fundet min, skal jeg tjekke om punkterne er connected,
				

				if (min > distance[i])
				{
					min = distance[i];
					index = i;
				}
			}

			// Hvis de er det, skal jeg add det til ChildNodes, som skal placeres på plads index i parent. 

			con = isconnected(Nodes[currentindex], Nodes[index], img);

			
			if (con == true)
			{
				parent[currentindex].push_back(Nodes[index]);
				int y = 0;
			}
			distance[index] = 1000000;
		}

	}

	

	return parent;

}

bool isconnected(Point Dad, Point Child, const Mat &img)
{
	double mindistance = 100000;
	double pixeldist;
	
	//Tjekker pixels mellem de to punkter.
	int minx;
	int miny;
	int localx = Dad.x;
	int localy = Dad.y;
	bool connected = false;

	while (localx != Child.x || localy != Child.y)
	{
		for (int i = localx - 1; i < localx + 2; i++)
		{
			for (int j = localy - 1; j < localy + 2; j++)
			{
				if (img.at<Vec3b>(i, j)[0] > 200)
				{
					pixeldist = sqrt((Child.x - i) * (Child.x - i) + (Child.y - j) * (Child.y - j));
					if (pixeldist < mindistance)
					{
						mindistance = pixeldist;
						minx = i;
						miny = j;
					}
				}
				else
				{
					return connected = false;
				}

			}
		}
		localx = minx;
		localy = miny;
	}

	return connected = true;

}

