#ifndef DATA_H
#define DATA_H
#include <vector>

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

#endif