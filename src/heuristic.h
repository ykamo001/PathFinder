#ifndef HEURISTIC_H
#define HEURISTIC_H
#include<vector>

using namespace std;

int manDist(vector<int> &a, vector<int> &b);		//use this function to find the total manhatan distance of node state
int missPlaced(vector<int> &a, vector<int> &b);	//use this function to find the heuristic score of miss placed tiles of node state

#endif