#include <vector>
#include <queue>
#include <iostream>
#include "util.h"
#include "heuristic.h"
#include "data.h"
#include "search.h"

using namespace std;

void move(Node expand, queue<Node> &a, vector<int> &b, char heurType) //use this function to expand all the states
{
	vector<vector<int> > hold = expand.path;
	int expandgn = expand.gn;
	int expandhn = expand.hn;
	int expandDepth = expand.depth;
	int expandTotal = expand.total;
	int expandBlank = expand.blank;
	vector<int> modify = hold.at(hold.size()-1);
	vector<int> parent;
	if(hold.size() > 1){
		parent = hold.at(hold.size()-2);
	}
	else{
		parent = hold.at(hold.size()-1);
	}

	vector<vector<int> > lib = hold;
	vector<int> use = modify;
	Node right = Node(lib, 1, 0, 1, 1, 1);
	bool right1 = false;
	Node left = Node(lib, 1, 0, 1, 1, 1);
	bool left1 = false;
	Node up = Node(lib, 1, 0, 1, 1, 1);
	bool up1 = false;
	Node down = Node(lib, 1, 0, 1, 1, 1);
	bool down1 = false;

	/*cout << "Expanding state: " << endl;
	for(int i=0; i < modify.size(); ++i) //output the current state
	{
		if((i == 3) || (i == 6))
		{
			cout << endl;
		}
		cout << modify.at(i) << " ";
	}
	cout << endl;
	cout << "With g(n) = " << expandgn << " and h(n) = " << expandhn << endl;*/

	int temp = 0;
	int missHeur = 0;
	int manHeur = 0;
	expandgn += 1;
	expandDepth += 1;
	if(expandBlank+1 <= 8) { //checks to see if we can move to the right
		if((expandBlank != 2) && (expandBlank != 5)) {	//only move right if it is not on the edge
			temp = use.at(expandBlank);
			use.at(expandBlank) = use.at(expandBlank+1);
			use.at(expandBlank+1) = temp;
			if(use != parent) { //checks to see if it is not a repeated state and going backwards
				lib.push_back(use);
				right1 = true;
				if(heurType == '1') { //for Uniform Cost Search
					right = Node(lib, expandgn, 0, expandDepth, expandgn, (expandBlank+1));
				}
				else if(heurType == '2') { //for miss placed tile heuristic
					missHeur = missPlaced(use, b);
					right = Node(lib, expandgn, missHeur, expandDepth, (expandgn+missHeur), (expandBlank+1));
				}
				else { //for manhattan distance heuristic
					manHeur = manDist(use, b);
					right = Node(lib, expandgn, manHeur, expandDepth, (expandgn+manHeur), (expandBlank+1));
				}
			}
		}
	}

	use = modify;
	lib = hold;
	if(expandBlank-1 >= 0) {//checks to see if we can move left
		if((expandBlank != 3) && (expandBlank != 6)) {	//check to see if it not on edge
			temp = use.at(expandBlank);
			use.at(expandBlank) = use.at(expandBlank-1);
			use.at(expandBlank-1) = temp;
			if(use != parent) {
				lib.push_back(use);
				left1 = true;
				if(heurType == '1') {	//for Uniform Cost Search
					left = Node(lib, expandgn, 0, expandDepth, expandgn, (expandBlank-1));
				}
				else if(heurType == '2') {	//for miss placed tile heuristic
					missHeur = missPlaced(use, b);
					left = Node(lib, expandgn, missHeur, expandDepth, (expandgn+missHeur), (expandBlank-1));
				}
				else {	//for manhattan distance heuristic
					manHeur = manDist(use, b);
					left = Node(lib, expandgn, manHeur, expandDepth, (expandgn+manHeur), (expandBlank-1));
				}
			}
		}
	}

	use = modify;
	lib = hold;
	if(expandBlank+3 <= 8) {		//check to see if we can move blank down
		temp = use.at(expandBlank);
		use.at(expandBlank) = use.at(expandBlank+3);
		use.at(expandBlank+3) = temp;
		if(use != parent) {	//checks to see if we are not going back to redundant node
			lib.push_back(use);
			down1 = true;
			if(heurType == '1')	{ //for Uniform Cost Search
				down = Node(lib, expandgn, 0, expandDepth, expandgn, (expandBlank+3));
			}
			else if(heurType == '2') {	//for miss placed tile heuristic
				missHeur = missPlaced(use, b);
				down = Node(lib, expandgn, missHeur, expandDepth, (expandgn+missHeur), (expandBlank+3));
			}
			else {	//for manhattan distance heuristic
				manHeur = manDist(use, b);
				down = Node(lib, expandgn, manHeur, expandDepth, (expandgn+manHeur), (expandBlank+3));
			}
		}
	}

	use = modify;
	lib = hold;
	if(expandBlank-3 >= 0) {//checks to see if we can move blank up
		temp = use.at(expandBlank);
		use.at(expandBlank) = use.at(expandBlank-3);
		use.at(expandBlank-3) = temp;
		if(use != parent) {	//make sure we are not going backwards and revisiting a node
			lib.push_back(use);
			up1 = true;
			if(heurType == '1')	{	//for Uniform Cost Search
				up = Node(lib, expandgn, 0, expandDepth, expandgn, (expandBlank-3));
			}
			else if(heurType == '2') {		//for miss placed tiles heuristic
				missHeur = missPlaced(use, b);
				up = Node(lib, expandgn, missHeur, expandDepth, (expandgn+missHeur), (expandBlank-3));
			}
			else {	//for manhattan distance heuristic
				manHeur = manDist(use, b);
				up = Node(lib, expandgn, manHeur, expandDepth, (expandgn+manHeur), (expandBlank-3));
			}
		}
	}

	if(right1) {	//only add onto queue the nodes that are present, otherwise skip
		a.push(right);
	}
	if(left1) {
		a.push(left);
	}
	if(up1) {
		a.push(up);
	}
	if(down1) {
		a.push(down);
	}

	if(heurType != '1') {	//only sort the queue if it is not uniform cost search, as nodes now have different total costs
		orderSort(a);	//call the sorting function
	}
}

void mySearch(vector<int> &start, vector<int> &finish, int &blank, char score)
{
	queue<Node> work;	//have queue of all the nodes
	vector<int> par;
	vector<vector<int> > lib;
	lib.push_back(start);
	work.push(Node(lib, 0, 0, 0, 0, blank));	//create initial node
	Node temp = work.front();
	bool done = false;
	bool success = false;
	int added = 0;
	int maxSize = work.size();
	while(!done)			//keep doing the search until we found a reason to stop
	{
		if(work.size() > maxSize) {	//keep track of biggest size of queue
			maxSize = work.size();
		}

		if(work.size() > 0)	{	//if there are nodes to be looked at, check if goal state, otherwise expand them
			temp = work.front();
			work.pop();
			lib = temp.path;
			par = lib.at(lib.size()-1);
			if(par == finish) {
				done = true;
				success = true;
			}
			else {
				move(temp, work, finish, score);	//function used to expand current state/node
				++added;			//keep track of how many nodes we have expanded
			}
		}
		else {
			done = true;
			success = false;
		}
	}
	if(success)	{	//if goal was found, output information
		cout << "Goal Found!" << endl;
		//cout << "In order to solve this problem, the algorithm expanded a total of " << added << " nodes." << endl;
		//cout << "The maximum number of nodes in the queue at any one time was " << maxSize << "." << endl;
		//cout << "The depth of the goal node is " << temp.depth << "." << endl;
		lib = temp.path;
		if(lib.size() > 1) {
			cout << "Total number of moves needed: " << lib.size()-2 << endl;
			cout << "Path:" << endl;
			for(int j = 0; j < lib.size(); j++) {
				par = lib.at(j);
				for(int i = 0; i < par.size(); i++) {
					if ((i == 3) || (i == 6)) {
						cout << endl;
					}
					cout << par.at(i) << " ";
				}
				cout << endl;
				if(j != lib.size()-1) {
					cout << "  |" << endl;
					cout << "  v" << endl;
				}
			}
		}
		else{
			cout << "Start state is goal state. No moves needed." << endl;
		}
	}
	else {
		cout << "No solution possible." << endl;
	}
}