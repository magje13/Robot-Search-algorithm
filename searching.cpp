#include "Header.h"

void searching(pos start, pos drop_point, const vector<pos> &nodes, vector<vector<pos>>&children, int sensor, double &traversed) {

	pos goal, current, next;
	vector<pos>goals = nodes;
	vector<pos>path;
	vector<pos>scanned;
	Mat image;
	bool found_it;
	string imageName = "Map.png";
	
	image = imread(imageName.c_str(), IMREAD_COLOR); 
	if (image.empty()) 
	{
		cout << "Could not open or find the image" << std::endl;
		
	}

	//pad billede for at kunne scanne med matrice i yderkanten af image
	Mat kopi = pad(image, sensor);

	current = start;

	while (goals.size() != 0) {

		
		////scanner område omkring current node, hvis node ikke i scanned[]..  LAV TIL FUNKTIONSKALD...
		//found_it = scanning(current, image, kopi, sensor, scanned, goals, traversed);

		//if (found_it) {

		//	//brug A* tilbage til drop_point. og sæt derefter drop_point til current.

		//}


		//for all nodes in goals[]

		for (int x = 0; x < goals.size(); x++) {

		
			goal = goals[x];
	
				//generates path of nodes, from current to first node in goals[]
			path = Astar(current, goal, nodes, children);

				//for all nodes in path, except last one, becasuse we dont draw FROM the last node.
			for (int y = 0; y < path.size() - 1; y++) {

				next.i = path[y + 1].i;
				next.j = path[y + 1].j;
					//draw beregner korteste linje mellem to noder og tegner 
				draw(image, current, next, traversed);
				namedWindow("test3", 0); imshow("test3",image); 
				waitKey(1);

					//opdaterer current til noden der netop er tegnet linje hen til.
				current = next;

				

			}

				//scanner område omkring current node, hvis node ikke i scanned[]..  Hey er det ikke unødvendigt at tjekke om den er scannet nu?
			found_it = scanning(current, image, kopi, sensor, scanned, goals, traversed);

			if (found_it) {
					//go back to droppoint. Use A* to find shortest path.
				path = Astar(current, drop_point, nodes, children);

					//for all nodes in path, except last one, becasuse we dont draw FROM the last node.
				for (int y = 0; y < path.size() - 1; y++) {

					next.i = path[y + 1].i;
					next.j = path[y + 1].j;
						//draw beregner korteste linje mellem to noder og tegner 
					draw(image, current, next, traversed);
					namedWindow("test3", 0); imshow("test3", image);
					waitKey(1);

						//opdaterer current til noden der netop er tegnet linje hen til.
					current = next;

				}
			}

		}


	}

}


void draw(Mat &image, pos current, pos next, double &traversed) {
	
	
		//draw m-line from current to next node
	pos min;
	double minDist = 99999999.0;
	double distance;
	pos evaluation;
	int i = current.i;
	int j = current.j;

	image.at<Vec3b>(i, j)[0] = 255;
	image.at<Vec3b>(i, j)[1] = 0;
	image.at<Vec3b>(i, j)[2] = 0;

	while (i != next.i || j != next.j) {

		

			//loops through a 3x3 matrix to find pixel shortest to next node
		for (int x = i - 1; x < i + 2; x++) {
			for (int y = j - 1; y < j + 2; y++) {

					//calculates and compares pixel distances
				evaluation.i = x;
				evaluation.j = y;
				distance = calcDist(next, evaluation);
				if (distance < minDist) {
					minDist = distance;
					min.i = x;
					min.j = y;
				}
			}
		}

		image.at<Vec3b>(min.i, min.j)[0] = 255;
		image.at<Vec3b>(min.i, min.j)[1] = 0;
		image.at<Vec3b>(min.i, min.j)[2] = 0;
		

		i = min.i;
		j = min.j;

		traversed += minDist;

	}

}
	

	
	


Mat pad(const Mat &image, int sensor) { //lavet til en maximal sensorrækkevidde på 50

	Mat clon = image.clone();
	int top, bottom, left, right;
	int borderType = BORDER_CONSTANT;
	const char* window_name = "copyMakeBorder Demo";


	top = sensor; bottom = sensor;
	left = sensor; right = sensor;

	copyMakeBorder(image, clon, top, bottom, left, right, borderType, 0);

	
	return clon;
}

bool scanning(pos current, Mat &image, Mat &kopi, const int &sensor, vector<pos> &scanned, vector<pos> &goals, double &traversed) {

	pos current2 = current;
	pos target;
	bool fund = false;

	bool alreadyScanned = false;


	for (int s = 0; s < scanned.size(); s++) {
		if (current.i == scanned[s].i && current.j == scanned[s].j) {

			//current is already scanned
			alreadyScanned = true;
			break;

		}
	}
	if (alreadyScanned == false) {

		//remove current from goals[] and adds to scanned[]
		for (int x = 0; x < goals.size(); x++) {

			if (current.i == goals[x].i && current.j == goals[x].j) {

				//removes from goals
				goals.erase(goals.begin() + x);
				scanned.push_back(current);
				break; // breaks search for current on goals[]
			}

		}
		//husk der skal arbejdes med padded billede. 
		for (int i = current.i; i < current.i + 2*sensor-1; i++) {
			
			for (int j = current.j; j < current.j +2*sensor-1; j++) {
							

				//fØLGENDE KRÆVER AT BILLEDE ER BGR-FORMAT
				//Hvis pixel er rød (mål):
 				if (kopi.at<Vec3b>(i, j)[0] <= 50 && kopi.at<Vec3b>(i, j)[1] <= 50 && kopi.at<Vec3b>(i, j)[2] >= 200) {

					fund = true;

					target.i = i-sensor;
					target.j = j-sensor;
					
					current2 = target;

					// fjerner målet fra kopi 
					kopi.at<Vec3b>(i, j)[0] = 255;
					kopi.at<Vec3b>(i, j)[1] = 255;
					kopi.at<Vec3b>(i, j)[2] = 255;

					//fjerner målet fra image
					image.at<Vec3b>(i-sensor, j-sensor)[0] = 255;
					image.at<Vec3b>(i-sensor, j-sensor)[1] = 255;
					image.at<Vec3b>(i-sensor, j-sensor)[2] = 255;

					
				}

			}

		}

		//her er du nået til

		draw(image, current, current2, traversed);

		draw(image, current2, current, traversed);

		return fund;

	}
	  	
}

