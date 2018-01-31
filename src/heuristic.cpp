#include <vector>
#include <map>
#include <algorithm>
#include "heuristic.h"

using namespace std;

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