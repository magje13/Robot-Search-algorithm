#include "Header.h"

vector<pos> convertNodes(const vector<Point> &Nod) {

	// x = i
	// y = j
	vector<pos> nodes;
	pos cord;

	for (int i = 0; i < Nod.size(); i++) {

		cord.i = Nod[i].x;
		cord.j = Nod[i].y;
		nodes.push_back(cord);

	}

	return nodes;
}

vector<vector<pos>> convertChildren(const vector<vector<Point>> &Child) {

	// x = i
	// y = j

	vector<vector<pos>> c;
	vector<pos> temp;
	pos cords;
	
	for (int i = 0; i < Child.size(); i++) {
		c.push_back(temp);
		
		for (int j = 0; j < Child[i].size(); j++) {
			
			cords.i = Child[i][j].x;
			cords.j = Child[i][j].y;

			c[i].push_back(cords);
			
		}
		
	}

	return c;
}