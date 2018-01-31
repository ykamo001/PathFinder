#include <vector>
#include <map>
#include <queue>
#include "util.h"
#include "data.h"

using namespace std;

bool valid(vector<int> &check) //used to check if goal/start state are correct in format and values
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