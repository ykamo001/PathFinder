#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <list>
#include <algorithm>

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

int manDist(vector<int> a, vector<int> &b)		//use this function to find the total manhatan distance of node state
{
	int goal[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
	int comp[3][3] = {{a.at(0), a.at(1), a.at(2)}, {a.at(3), a.at(4), a.at(5)}, {a.at(6), a.at(7), a.at(8)}};
	int totaldiff = 0;
	int deltx = 0;
	int delty = 0;
	int look = 0;
	for(int k = 0; k < 3; ++k)
	{
		for(int l = 0; l < 3; ++l)
		{
			look = comp[k][l];
			for(int i = 0; i < 3; ++i)
			{
				for(int j = 0; j < 3; ++j)
				{
					if(goal[i][j] == look)
					{
						deltx = abs(k - i);
						delty = abs(l - j);
						totaldiff = (totaldiff + (deltx + delty));
					}
				}
			}
		}
	}
	return totaldiff;
}

int missPlaced(vector<int> a, vector<int> &b)	//use this function to find the heuristic score of miss placed tiles of node state
{
	int diff = 0;
	for(int i = 0; i < a.size(); ++i)
	{
		if(a.at(i) != b.at(i))
		{
			++diff;
		}
	}
	return diff;
}

void move(Node expand, queue<Node> &a, vector<int> &b, int &heurType) //use this function to expand all the states
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
				if(heurType == 1)	//for Uniform Cost Search
				{
					right = Node(use, expandgn, 0, (expandDepth+1), expandgn, (expandBlank+1), modify);
				}
				else if(heurType == 2)	//for miss placed tile heuristic
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
				if(heurType == 1)	//for Uniform Cost Search
				{
					left = Node(use, expandgn, 0, (expandDepth+1), expandgn, (expandBlank-1), modify);
				}
				else if(heurType == 2)	//for miss placed tile heuristic
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
			if(heurType == 1)	//for Uniform Cost Search
			{
				up = Node(use, expandgn, 0, (expandDepth+1), (expandgn+1), (expandBlank+3), modify);
			}
			else if(heurType == 2)		//for miss placed tile heuristic
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
			if(heurType == 1)		//for Uniform Cost Search
			{
				down = Node(use, expandgn, 0, (expandDepth+1), (expandgn+1), (expandBlank-3), modify);
			}
			else if(heurType == 2)		//for miss placed tiles heuristic
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
	if(heurType != 1)	//only sort the queue if it is not uniform cost search, as nodes now have different total costs
	{
		orderSort(a);	//call the sorting function
	}
}

void mySearch(vector<int> &start, vector<int> &finish, int &blank, int &score)
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

void getInput(vector<int> &store) //this function takes in the user inputs for the starting puzzle
{
	char input;
	int keep;
	bool invalid = false;
	vector<int> temp;
	for(int i=0; i < 3; ++i)
	{
		cin >> input;
		if((input < '0') || (input > '8') && (input != ' ')) //do some error checking, only take in numbers
		{
			invalid = true;
		}
		else
		{
			if(input != ' ') //store the inputs in a temp vector only if the input was valid and not a space
			{
				keep = input - '0';
				temp.push_back(keep);
			}
		}
	}
	if(invalid) //if we found any invalid inputs, recursively call this function until proper inputs are made
	{
		cout << "You entered invalid characters, please re-enter your row: ";
		temp.clear();		//make sure to wipe out the inputs before calling the function again
		getInput(temp);
	}
	for(int i=0; i < temp.size(); ++i) //push the inputs back into the initial vector
	{
		store.push_back(temp.at(i));
	}
}

int main()
{
	vector<int> init;
	cout << "Please enter your puzzle and use a 0 to represent a blank" << endl;
	bool okay = false;
	int counter = 0;
	while(!okay) //take in user inputs until user gets proper initial puzzle set-up
	{
		counter = 0;
		cout << "Enter your first row, use space to seperate inputs: ";
		getInput(init);
		cout << "Enter your second row, use space to seperate inputs: ";
		getInput(init);
		cout << "Enter your third row, use space to seperate inputs: ";
		getInput(init);
		for(int i=0; i < init.size(); ++i) //check if a blank space was entered only once
		{
			if(init.at(i) == 0)
			{
				counter++;
			}
		}
		if(counter == 0)
		{
			cout << "You did not enter in a blank! Please re-enter your puzzle." << endl;
			init.clear();
		}
		else if(counter == 1)
		{
			okay = true;
		}
		else
		{
			cout << "You entered too many blanks! Please re-enter your puzzle." << endl;
			init.clear();
		}
	}
	cout << endl << "Your input puzzle is: " << endl;
	for(int i=0; i < init.size(); ++i) //output the initial puzzle to show user
	{
		if((i == 3) || (i == 6))
		{
			cout << endl;
		}
		cout << init.at(i) << " ";
	}
	cout << endl;
	vector<int> goal;	//create the goal state so we have something to compare to and know when we are done
	goal.push_back(1);
	goal.push_back(2);
	goal.push_back(3);
	goal.push_back(4);
	goal.push_back(5);
	goal.push_back(6);
	goal.push_back(7);
	goal.push_back(8);
	goal.push_back(0);
	
	int blankLoc = 0;	//finds the initial blank location
	for(int i=0; i < init.size(); ++i)
	{
		if(init.at(i) == 0)
		{
			blankLoc = i;
		}
	}
	cout << "Your blank is located at: " << blankLoc << endl << endl;
	okay = false;
	int choice = 0;
	while(!okay)
	{
		cout << "Please enter the algorithm you would like to run: " << endl;
		cout << "1. Uniform Cost Search" << endl;
		cout << "2. A* with Misplaced Tile Heuristic" << endl;
		cout << "3. A* with Manhatten Heurisitc" << endl;
		cout << "Algorithm: ";
		cin >> choice;
		if((choice >= 1) && (choice <= 3))
		{
			okay = true;
		}
		else
		{
			cout << "Invalid choice!" << endl;
		}
	}
	cout << endl;
	if(choice == 1)
	{
		mySearch(init, goal, blankLoc, choice);
	}
	else if(choice == 2)
	{
		mySearch(init, goal, blankLoc, choice);
	}
	else 
	{
		mySearch(init, goal, blankLoc, choice);
	}
	return 0;
}