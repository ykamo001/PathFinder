#ifndef SEARCH_H
#define SEARCH_H
#include <vector>
#include <queue>
#include "data.h"

using namespace std;

void move(Node expand, queue<Node> &a, vector<int> &b, char heurType); //use this function to expand all the states
void mySearch(vector<int> &start, vector<int> &finish, int &blank, char score);

#endif