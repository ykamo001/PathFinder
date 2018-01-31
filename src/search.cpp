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
	expandgn += 1;
	expandDepth += 1;
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
					right = Node(use, expandgn, 0, expandDepth, expandgn, (expandBlank+1), modify);
				}
				else if(heurType == '2')	//for miss placed tile heuristic
				{
					missHeur = missPlaced(use, b);
					right = Node(use, expandgn, missHeur, expandDepth, (expandgn+missHeur), (expandBlank+1), modify);
				}
				else	//for manhattan distance heuristic
				{
					manHeur = manDist(use, b);
					right = Node(use, expandgn, manHeur, expandDepth, (expandgn+manHeur), (expandBlank+1), modify);
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
					left = Node(use, expandgn, 0, expandDepth, expandgn, (expandBlank-1), modify);
				}
				else if(heurType == '2')	//for miss placed tile heuristic
				{
					missHeur = missPlaced(use, b);
					left = Node(use, expandgn, missHeur, expandDepth, (expandgn+missHeur), (expandBlank-1), modify);
				}
				else		//for manhattan distance heuristic
				{
					manHeur = manDist(use, b);
					left = Node(use, expandgn, manHeur, expandDepth, (expandgn+manHeur), (expandBlank-1), modify);
				}
			}
		}
	}
	use = modify;
	if(check+3 <= 8)		//check to see if we can move blank down
	{
		temp = use.at(check);
		use.at(check) = use.at(check+3);
		use.at(check+3) = temp;
		if(use != expand.parent)	//checks to see if we are not going back to redundant node
		{
			down1 = true;
			if(heurType == '1')	//for Uniform Cost Search
			{
				down = Node(use, expandgn, 0, expandDepth, expandgn, (expandBlank+3), modify);
			}
			else if(heurType == '2')		//for miss placed tile heuristic
			{
				missHeur = missPlaced(use, b);
				down = Node(use, expandgn, missHeur, expandDepth, (expandgn+missHeur), (expandBlank+3), modify);
			}
			else		//for manhattan distance heuristic
			{
				manHeur = manDist(use, b);
				down = Node(use, expandgn, manHeur, expandDepth, (expandgn+manHeur), (expandBlank+3), modify);
			}
		}
	}
	use = modify;
	if(check-3 >= 0)	//checks to see if we can move blank up
	{
		temp = use.at(check);
		use.at(check) = use.at(check-3);
		use.at(check-3) = temp;
		if(use != expand.parent)	//make sure we are not going backwards and revisiting a node
		{
			up1 = true;
			if(heurType == '1')		//for Uniform Cost Search
			{
				up = Node(use, expandgn, 0, expandDepth, expandgn, (expandBlank-3), modify);
			}
			else if(heurType == '2')		//for miss placed tiles heuristic
			{
				missHeur = missPlaced(use, b);
				up = Node(use, expandgn, missHeur, expandDepth, (expandgn+missHeur), (expandBlank-3), modify);
			}
			else		//for manhattan distance heuristic
			{
				manHeur = manDist(use, b);
				up = Node(use, expandgn, manHeur, expandDepth, (expandgn+manHeur), (expandBlank-3), modify);
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