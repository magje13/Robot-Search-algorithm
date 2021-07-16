#include "Header.h"

vector<pos>Astar(pos start, pos goal, const vector<pos> &nodes, vector<vector<pos>> &children) {

	double h = 0;
	double g = 0.0;
	double f = 0.0;
	double f_min;
	vector<pos>openList;	//consists of nodes that have been visited but not expanded (meaning that sucessors have not been explored yet).This is the list of pending tasks
	vector<pos>closedList; // consists of nodes that have been visited and expanded (sucessors have been explored already and included in the open list, if this was the case).
	pos current_node;
	vector<pos>path;

	closedList.erase(closedList.begin(), closedList.end());


	//put the startNode on the openList (leave it's f at zero)
	start.f = 0;
	start.h = 0;
	start.g = 0;
	openList.push_back(start);
	goal.f = 0;
	goal.h = 0;
	goal.g = 0;

	// søg indtil openlist er tom (alle noder er evalueret)
	while (!openList.empty()) {


		// let the currentNode equal the node with the least f value, in the openlist
		int current_node_index = 0;
		openList.at(current_node_index).f = calcDist(goal, openList.at(current_node_index)) + openList.at(current_node_index).g;
		current_node = openList.at(current_node_index);
		f_min = current_node.f;


		for (int i = 0; i < openList.size(); i++) {
			f = calcDist(goal, openList.at(i)) + openList.at(i).g; //f = h+g

			if (f < f_min) {

				current_node = openList.at(i);

				current_node.f = f;		// sæt nodens f-værdi
				current_node_index = i;			// gem nodens index

			}

		}

		//register parent node

		//remove node from openList and add to closedList
		closedList.push_back(current_node);
		openList.erase(openList.begin() + current_node_index); //	openList.pop(current_node_index); 

		//check if nodes is goal
		if (current_node.i == goal.i && current_node.j == goal.j) {
			/*cout << " You found goal - the path will be returned as a vector" << endl;*/


			return createPath(closedList, current_node, start, goal);

		}

		bool child_in_closed;
		bool child_in_open;

		// loop through each children of current node


		for (int i = 0; i < nodes.size(); i++) {

			//finds current node in vector of nodes

			if (current_node.i == nodes.at(i).i && current_node.j == nodes.at(i).j) {

				for (int j = 0; j < children[i].size(); j++) {

					// resetter bool til false inden søgning
					child_in_closed = false;

					for (int k = 0; k < closedList.size(); k++) {

						//child er i closedList;
						if (children[i][j].i == closedList[k].i && children[i][j].j == closedList[k].j) {

							child_in_closed = true;
							break;

						}

					}

					// Create the f, g, and h values for children som ikke er i closedList
					if (child_in_closed == false) {

						children[i][j].g = current_node.g + calcDist(children[i][j], current_node); // g = current g + afstand til child.
						children[i][j].h = calcDist(children[i][j], goal);
						children[i][j].f = children[i][j].g + children[i][j].h;

					}
					else {
						continue;
					}

					// tjekker om child er i open. Childs i closed bør være sprunget over...

					child_in_open = false;
					double openList_g;

					//  leder efter child i openlist
					for (int k = 0; k < openList.size(); k++) {

						//child er i openList;
						if (children[i][j].i == openList[k].i && children[i][j].j == openList[k].j) {

							child_in_open = true;
							openList_g = openList[k].g;
							break;

						}

					}

					if (child_in_open == false) {

						//saves parent node
						children[i][j].parent_i = current_node.i;
						children[i][j].parent_j = current_node.j;

						openList.push_back(children[i][j]);


					}
					else {
						if (children[i][j].g <= openList_g) {
							//saves parent node
							openList.push_back(children[i][j]);
						}
					}



				}


				break;

			}



		}

	}


}

double calcDist(pos goal, pos current) {

	int i_s = current.i;
	int j_s = current.j;
	int i_g = goal.i;
	int j_g = goal.j;

	double d = sqrt((pow((i_g - i_s), 2)) + (pow((j_g - j_s), 2)));		//squareroot overflødig
	return d;
}

vector<pos>createPath(const vector<pos> &closedList, pos current_node, pos start, pos goal) {

	vector<pos>p;



	while (current_node.i != start.i || current_node.j != start.j) {

		p.push_back(current_node);

		for (int i = 0; i < closedList.size(); i++) {

			if (closedList[i].i == current_node.parent_i && closedList[i].j == current_node.parent_j) {

				current_node = closedList[i];


			}
		}


	}
	p.push_back(start);
	reverse(p.begin(), p.end());
	return p;

}



pos::pos()
{
}


pos::~pos()
{
}

