#include "Header.h"
#include "opencv2/opencv.hpp"
#include <opencv/highgui.h>
#include <iostream>
#include <string>
#include <vector>


int main()
{
		
		//Roadmap afsnittet

		//Vektoren med noder Robotten kan besøge	
	vector<Point> bluenodes;
		//Vector af vector, som viser hvilke noder den enkelte node er forbundet til
	vector<vector<Point>> Neighbors;

		//Indlæser billedet 
	Mat Map = imread("Map.png", 1);
	
		//Fjerner de røde mål, for at lave brushfire
	Mat graymap = editcolor(Map);
	
		//Laver Brushfire
	Mat img = Brushfire(graymap);
	
		//Laver Voronoi
	Mat vor = Voronoi(img);
	
		//Finder noder og gemmer dem i vectoren bluenodes 
	Mat node = Nodes(vor,bluenodes);
	
		//Indsætter noderne på Mappet
	Mat MapWithNodes = Mapnodes(Map, bluenodes);

		//Tilføjer start punktet til vectoren med noderen. 
	bluenodes.insert(bluenodes.begin(), Point(10,10));

		//Laver en vector af vector<Point> for at finde de noder de enkelte noder kan besøge
	Neighbors = Child(Neighbors, bluenodes, MapWithNodes);


	//Robot bevægelses afsnittet 

		//angiv startpunkt, droppoint og sensorrækkevidde:
	int sensor = 35;
	pos start, drop_point;

	start.i = 10;
	start.j = 10;

	drop_point.i = 10;
	drop_point.j = 10;
		

		//containers initialiseres
	vector<pos> nodes;
	vector<vector<pos>> children;
	vector<pos>path;
		
		//Her konvertere vi nodernn til et format vi kan bruge i A*
	nodes = convertNodes(bluenodes); 

	children = convertChildren(Neighbors);
		//The traversed distance in pixels
	double traversed = 0;
	//pos node10_10, node15_14, node52_51, node52_60, node89_14, node15_97, node81_89, node82_131, node66_174, node15_123, node15_226, node103_174;
	//node10_10.i = 10;
	//node10_10.j = 10;

	//node15_14.i = 15;
	//node15_14.j = 14;

	//node52_51.i = 52;
	//node52_51.j = 51;

	//node89_14.i = 89;
	//node89_14.j = 14;

	//node52_60.i = 52;
	//node52_60.j = 60;

	//node15_97.i = 15;
	//node15_97.j = 97;

	//node81_89.i = 81;
	//node81_89.j = 89;

	//node82_131.i = 82;
	//node82_131.j = 131;

	//node66_174.i = 66;
	//node66_174.j = 174;

	//node15_123.i = 15;
	//node15_123.j = 123;

	//node15_226.i = 15;
	//node15_226.j = 226;

	//node103_174.i = 103;
	//node103_174.j = 174;


	//nodes = { node10_10, node15_14, node52_51, node89_14, node52_60, node15_97, node81_89, node82_131, node66_174, node15_123, node15_226, node103_174};
	//children = { {node15_14}, {node10_10, node52_51}, {node15_14, node52_60, node89_14}, {node52_51}, {node52_51, node15_97, node81_89}, {node52_60}, {node52_60, node82_131}, {node81_89, node66_174, node103_174}, {node82_131, node15_123, node15_226}, {node66_174}, {node66_174}, {node82_131} };

		//Besøg samtlige noder i nodes[] ved hjælp af A* søgealgortime, og scan omkring disse noder for at finde mål.
	searching(start, drop_point, nodes, children, sensor, traversed);
	cout << "\n traversed distance, in pixels: " << traversed << endl;
	

	waitKey(0);
	system("pause");
	return 0;
}