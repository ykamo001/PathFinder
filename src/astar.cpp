#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <list>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

class Node{		//sets up the node to hold all the different elements needed, like g(n), h(n), and depth
	public:
		vector<int> state;
		int gn;
		int hn;
		int depth;
		int total;
		int blank;
		vector<int> parent;
		Node(vector<int> a, int b, int c, int d, int e, int f, vector<int> g) 
		{
			this->state = a; 
			this->gn = b;
			this->hn = c;
			this->depth = d; 
			this->total = e; 
			this->blank = f; 
			this->parent = g;
		}
};

vector<Node> merge(vector<Node> a, vector<Node> b)		//use this function in conjunction with merge sort to bring container together
{
	vector<Node> c;
	int i = 0;
	int j = 0;
	while((i < a.size()) && (j < b.size()))
	{
		Node look = a.at(i);
		Node there = b.at(j);
		if(look.total > there.total)
		{
			c.push_back(there);
			++j;
		}
		else
		{
			c.push_back(look);
			++i;
		}
	}
	while(i < a.size())
	{
		Node look = a.at(i);
		c.push_back(look);
		++i;
	}
	while(j < b.size())
	{
		Node there = b.at(j);
		c.push_back(there);
		++j;
	}
	return c;
}

vector<Node> mergesort(vector<Node> arr)	//sorts the queue in order of least expansive node to expand
{
	if(arr.size() == 1)
	{
		return arr;
	}
	vector<Node> l1;
	int left = arr.size()/2;
	for(int i = 0; i < left; ++i)
	{
		l1.push_back(arr.at(i));
	}
	vector<Node> r1;
	for(int i = left; i < arr.size(); ++i)
	{
		r1.push_back(arr.at(i));
	}
	l1 = mergesort(l1);
	r1 = mergesort(r1);

	return merge(l1, r1);
}

void orderSort(queue<Node> &input)  //use this function to setup and call for merge sort
{
	vector<Node> holder;
	while(input.size() > 0)
	{
		holder.push_back(input.front());
		input.pop();
	}
	holder = mergesort(holder);
	for(int i = 0; i < holder.size(); ++i)
	{
		input.push(holder.at(i));
	}
}

int manDist(vector<int> &a, vector<int> &b)		//use this function to find the total manhatan distance of node state
{
	map<int, pair<int, int> > grid;
	map<int, pair<int, int> >::iterator itr;
	int x, y, deltaX, deltaY, totaldiff;

	for(int i = 0; i < b.size(); i++){
		x = i/3;
		y = i%3;
		grid.insert(pair<int, pair<int, int> >(b.at(i), pair<int, int>(x, y)));
	}

	totaldiff = 0;
	for(int i = 0; i < a.size(); i++){
		x = i/3;
		y = i%3;
		itr = grid.find(a.at(i));
		deltaX = abs(x - itr->second.first);
		deltaY = abs(y - itr->second.second);
		totaldiff = totaldiff + (deltaX + deltaY);
	}

	return totaldiff;
}

int missPlaced(vector<int> &a, vector<int> &b)	//use this function to find the heuristic score of miss placed tiles of node state
{
	int diff = 0;
	for(int i = 0; i < a.size(); ++i) {
		if(a.at(i) != b.at(i)) {
			++diff;
		}
	}
	return diff;
}

void move(Node expand, queue<Node> &a, vector<int> &b, char heurType) //use this function to expand all the states
{
	int expandgn = expand.gn;
	int expandhn = expand.hn;
	int expandDepth = expand.depth;
	int expandTotal = expand.total;
	int expandBlank = expand.blank;
	int check = expand.blank;
	vector<int> modify = expand.state;
	vector<int> use = modify;
	Node right = Node(use, 1, 0, 1, 1, 1, modify);
	bool right1 = false;
	Node left = Node(use, 1, 0, 1, 1, 1, modify);
	bool left1 = false;
	Node up = Node(use, 1, 0, 1, 1, 1, modify);
	bool up1 = false;
	Node down = Node(use, 1, 0, 1, 1, 1, modify);
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
	expandgn = expandgn + 1;
	if(check+1 <= 8)		//checks to see if we can move to the right
	{
		if((check != 2) && (check != 5))	//only move right if it is not on the edge
		{
			temp = use.at(check);
			use.at(check) = use.at(check+1);
			use.at(check+1) = temp;
			if(use != expand.parent)	//checks to see if it is not a repeated state and going backwards
			{
				right1 = true;
				if(heurType == '1')	//for Uniform Cost Search
				{
					right = Node(use, expandgn, 0, (expandDepth+1), expandgn, (expandBlank+1), modify);
				}
				else if(heurType == '2')	//for miss placed tile heuristic
				{
					missHeur = missPlaced(use, b);
					right = Node(use, expandgn, missHeur, (expandDepth+1), (expandgn+missHeur), (expandBlank+1), modify);
				}
				else	//for manhattan distance heuristic
				{
					manHeur = manDist(use, b);
					right = Node(use, expandgn, manHeur, (expandDepth+1), (expandgn+manHeur), (expandBlank+1), modify);
				}
			}
		}
	}
	use = modify;
	if(check-1 >= 0)	//checks to see if we can move left
	{
		if((check != 3) && (check != 6))	//check to see if it not on edge
		{
			temp = use.at(check);
			use.at(check) = use.at(check-1);
			use.at(check-1) = temp;
			if(use != expand.parent)
			{
				left1 = true;
				if(heurType == '1')	//for Uniform Cost Search
				{
					left = Node(use, expandgn, 0, (expandDepth+1), expandgn, (expandBlank-1), modify);
				}
				else if(heurType == '2')	//for miss placed tile heuristic
				{
					missHeur = missPlaced(use, b);
					left = Node(use, expandgn, missHeur, (expandDepth+1), (expandgn+missHeur), (expandBlank-1), modify);
				}
				else		//for manhattan distance heuristic
				{
					manHeur = manDist(use, b);
					left = Node(use, expandgn, manHeur, (expandDepth+1), (expandgn+manHeur), (expandBlank-1), modify);
				}
			}
		}
	}
	use = modify;
	if(check+3 <= 8)		//check to see if we can move blank up
	{
		temp = use.at(check);
		use.at(check) = use.at(check+3);
		use.at(check+3) = temp;
		if(use != expand.parent)	//checks to see if we are not going back to redundant node
		{
			up1 = true;
			if(heurType == '1')	//for Uniform Cost Search
			{
				up = Node(use, expandgn, 0, (expandDepth+1), (expandgn+1), (expandBlank+3), modify);
			}
			else if(heurType == '2')		//for miss placed tile heuristic
			{
				missHeur = missPlaced(use, b);
				up = Node(use, expandgn, missHeur, (expandDepth+1), (expandgn+missHeur), (expandBlank+3), modify);
			}
			else		//for manhattan distance heuristic
			{
				manHeur = manDist(use, b);
				up = Node(use, expandgn, manHeur, (expandDepth+1), (expandgn+manHeur), (expandBlank+3), modify);
			}
		}
	}
	use = modify;
	if(check-3 >= 0)	//checks to see if we can move blank down
	{
		temp = use.at(check);
		use.at(check) = use.at(check-3);
		use.at(check-3) = temp;
		if(use != expand.parent)	//make sure we are not going backwards and revisiting a node
		{
			down1 = true;
			if(heurType == '1')		//for Uniform Cost Search
			{
				down = Node(use, expandgn, 0, (expandDepth+1), (expandgn+1), (expandBlank-3), modify);
			}
			else if(heurType == '2')		//for miss placed tiles heuristic
			{
				missHeur = missPlaced(use, b);
				down = Node(use, expandgn, missHeur, (expandDepth+1), (expandgn+missHeur), (expandBlank-3), modify);
			}
			else		//for manhattan distance heuristic
			{
				manHeur = manDist(use, b);
				down = Node(use, expandgn, manHeur, (expandDepth+1), (expandgn+manHeur), (expandBlank-3), modify);
			}
		}
	}
	if(right1)	//only add onto queue the nodes that are present, otherwise skip
	{
		a.push(right);
	}
	if(left1)
	{
		a.push(left);
	}
	if(up1)
	{
		a.push(up);
	}
	if(down1)
	{
		a.push(down);
	}
	if(heurType != '1')	//only sort the queue if it is not uniform cost search, as nodes now have different total costs
	{
		orderSort(a);	//call the sorting function
	}
}

void mySearch(vector<int> &start, vector<int> &finish, int &blank, char score)
{
	queue<Node> work;	//have queue of all the nodes
	vector<int> par;
	work.push(Node(start, 0, 0, 0, 0, blank, par));		//create initial node
	Node temp = work.front();
	bool done = false;
	bool success = false;
	int added = 0;
	int maxSize = work.size();
	while(!done)			//keep doing the search until we found a reason to stop
	{
		if(work.size() > maxSize)		//keep track of biggest size of queue
		{
			maxSize = work.size();
		}

		if(work.size() > 0)		//if there are nodes to be looked at, check if goal state, otherwise expand them
		{
			temp = work.front();
			work.pop();
			if(temp.state == finish)
			{
				done = true;
				success = true;
			}
			else
			{
				move(temp, work, finish, score);	//function used to expand current state/node
				++added;			//keep track of how many nodes we have expanded
			}
		}
		else
		{
			done = true;
			success = false;
		}
	}
	if(success)		//if goal was found, output information
	{
		cout << "Goal Found!" << endl;
		cout << "In order to solve this problem, the algorithm expanded a total of " << added << " nodes." << endl;
		cout << "The maximum number of nodes in the queue at any one time was " << maxSize << "." << endl;
		cout << "The depth of the goal node is " << temp.depth << "." << endl;
	}
}

bool valid(vector<int> &check)
{
	map<int, int> lib;
	map<int, int>::iterator itr;
	int num;
	if(check.size() == 9) {
		for(int i = 0; i < check.size(); i++) {
			num = check.at(i);
			if(num < 0 || num > 8) {
				return false;
			}
			else {
				itr = lib.find(num);
				if (itr == lib.end()) {
					lib.insert(pair<int, int>(num, 0));
				}
				else {
					return false;
				}
			}
		}
		return true;
	}
	else {
		return false;
	}
}

int main(int argc, char **argv)
{
	if(argc == 4) {
		vector<int> init;	//where to store the initial state
		vector<int> goal;	//our goal state
		string hold = "";
		int num;
		int blankLoc = 0;
		ifstream file;

		if(*argv[3] < '1' || *argv[3] > '3'){
			cout << "You have entered an invalid option for your algorithm selection. PLease choose either 1, 2, or 3." << endl;
			return 0;
		}

		file.open(argv[1]);
		while(getline(file, hold)) {	//pull the current puzzle condition 
			istringstream iss(hold);
			while(iss >> num){		//parse the string by space
				init.push_back(num);	//convert to number, then save 
			}
		}
		file.close();	//close file since we no longer need it
		hold = "";
		
		if(!valid(init)){
			cout << "Your initial puzzle is not correct. ";
			cout << "Remember to have only one instance of a number from 1-8, and a 0 for your space." << endl;
			return 0;
		}
		else {
			cout << "This is your start state:" << endl;
			for(int i=0; i < init.size(); ++i) {//output the initial puzzle to show user
				if((i == 3) || (i == 6)) {
					cout << endl;
				}
				cout << init.at(i) << " ";
				if(init.at(i) == 0){
					blankLoc = i;	//locate where the blank is initially located
				}
			}
			cout << endl;
		}

		file.open(argv[2]);
		while(getline(file, hold)) {	//pull the goal state 
			istringstream iss(hold);
			while(iss >> num){		//parse the string by space
				goal.push_back(num);	//convert to number, then save
			}
		}
		file.close();	//close file since we no longer need it

		if(!valid(goal)) {
			cout << "Your goal state is not correct. ";
			cout << "Remember to have only one instance of a number from 1-8, and a 0 for your space." << endl;
			return 0;
		}
		else {
			cout << "This is your goal state: " << endl;
			for(int i = 0; i < goal.size(); i++) {
				if ((i == 3) || (i == 6)) {
					cout << endl;
				}
				cout << goal.at(i) << " ";
			}
			cout << endl;
		}
		mySearch(init, goal, blankLoc, *argv[3]);
	}
	else {
		cout << "You did not enter the correct amount of arguments. ";
		cout << "Remember to enter the initial puzzle state file, goal state file, and algorithm option." << endl;
	}
	return 0;
}
