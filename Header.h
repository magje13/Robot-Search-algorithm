#pragma once

#include "opencv2/opencv.hpp"
#include <opencv/highgui.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>   

using namespace std;
using namespace cv;

Mat editcolor(Mat& img);

Mat Brushfire(Mat& img);

Mat Voronoi(Mat& img);

Mat Nodes(Mat& img, vector<Point>& Nodes);

Mat Mapnodes(Mat& img, vector<Point>& Nodes);

vector<vector <Point>> Child(vector<vector <Point>>& parent, vector<Point>& Nodes, Mat& img);

bool isconnected(Point Dad, Point Child,  const Mat& img);

class pos
{
public:
	pos();
	~pos();

	int i, j;
	double g = 0.0; //dist between current and start node
	double h = 0.0; // Heuristic between current and goal 
	double f = 0.0; //total cost
	int parent_i, parent_j;

};

double calcDist(pos goal, pos current);

vector<pos>Astar(pos start, pos goal, const vector<pos>& nodes, vector<vector<pos>>& children);

vector<pos>createPath(const vector<pos>& closedList, pos current_node, pos start, pos goal);

void searching(pos start, pos drop_point, const vector<pos>& nodes, vector<vector<pos>>& children, int sensor, double& traversed);

void draw(Mat& image, pos current, pos next, double& traversed);

bool scanning(pos current, Mat& image, Mat& kopi, const int& sensor, vector<pos>& scanned, vector<pos>& goals, double& traversed);

Mat pad(const Mat& image, int sensor);

vector<pos> convertNodes(const vector<Point>& Nod);

vector<vector<pos>> convertChildren(const vector<vector<Point>>& Child);