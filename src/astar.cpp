#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <list>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <map>
#include "heuristic.h"
#include "util.h"
#include "data.h"
#include "search.h"

using namespace std;

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
