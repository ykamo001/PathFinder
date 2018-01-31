#ifndef UTIL_H
#define UTIL_H
#include <vector>
#include <queue>
#include "data.h"

using namespace std;

bool valid(vector<int> &check); //used to check if goal/start state are correct in format and values
vector<Node> merge(vector<Node> a, vector<Node> b);		//use this function in conjunction with merge sort to bring container together
vector<Node> mergesort(vector<Node> arr);	//sorts the queue in order of least expansive node to expand
void orderSort(queue<Node> &input);  //use this function to setup and call for merge sort

#endif