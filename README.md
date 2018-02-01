# PathFinder
PathFinder is a search application that implements Artificial Intelligence properties like the ['A*'](https://en.wikipedia.org/wiki/A*_search_algorithm) algorithm and ['admissible heuristics'](https://en.wikipedia.org/wiki/Admissible_heuristic) to determine if a solution for an 8-puzzle exists or not, and determines the path needed to reach the solution with minimal moves. 
An [8-puzzle](https://en.wikipedia.org/wiki/15_puzzle) is a version of the classic 15-puzzle game, also referred to as the N-puzzle, where you have the numbers 1-8, and an empty space, all out of order, and have to arrange them sequentially such that it starts with 1, and ends with the empty space.

Here's an example of a starting state and the final result:

![alt text](https://pravj.github.io/images/states.jpg)

## Installing and Running
To get ASTAR and run it, please open up a terminal and run these commands:
```
git clone https://github.com/ykamo001/PathFinder.git
cd PathFinder/
make
./src/astar.out ./puzzles/1.txt ./puzzles/goal.txt 3
```

With my implementation, after you have entered in a desired puzzle to solve, you are able to pick a search algorithm.
Each of these algorithms find the solution in a different way, each using a different heuristic score. 

The 3 algorithms you can choose from are: 

1. [Uniform Cost Search](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm#Practical_optimizations_and_infinite_graphs)
2. A* With [Misplaced Tile Heuristic](https://heuristicswiki.wikispaces.com/Misplaced+Tiles)
3. A* With [Manhatten Heuristic](https://heuristicswiki.wikispaces.com/Manhattan+Distance)

If the goal state can be found, then the program will terminate and output some information regarding the search. For now, the nodes that are expaned are not outputted, but if you so desire, you can uncomment the code and it will output each state that is expanded in order until completion.

## Findings
From running multiple random puzzles, it can be seen that when using my algorithm, the Manhattan distance A* is the fastest and most optimal choice to find the goal state. 
It always has the least amount of nodes expanded, and this is due to the fact that there is a basis that will allow each node to be reordered. 
With uniform cost search, which takes the longest to do, as each cost is basically the depth, the queue of nodes cannot be rearranged or sorted, since they are already in order, as each expanded node will have one score higher of cost. 
The misplaced tile heuristic actually does it better than the uniform cost search as well, and sometimes resembles that of the manhattan distance, but can do worse than the manhattan too. 
This is due to the fact that the misplaced heuristic allows for a way to arrange and order the nodes, rather than having to leave them in the order they are found. 
Uniform cost search also always has the most number of nodes in the queue at one time, and this is because even if the goal state was found from an expanded node, it will not be able to reach the top of the queue until all the other nodes in front of it has had a chance to be expanded. 
This can cause the size complexity to be very high, but uniform cost search does have it's up side. 
I have noticed that uniform cost search is a lot faster to run compared to both A* algorithms with heuristics. 
This is probably due to the fact that both heuristics require the queue to be sorted every time a node is expanded. 
I implemented merge-sort to sort the queue, and the time complexity of that is O(nlogn), where n is the size of the queue. 
This can take quite some time when the queue has a big number of elements and is a trade off to find the most optimal solution, along with saving memory. 
I can see how if memory and optimality were an issue, uniform cost search would never be an option, but I am very impressed by the speed at which it can find solutions sometimes. 
Sometimes is also a big issue, meaning that it's not always guaranteed that uniform cost search will work very fast, there are certain times that manhattan beats uniform in finding the goal state. 
I noticed that manhattan is better than misplaced, and by better, I mean it expands less nodes and has less nodes in the queue at any given time. 
This might be the case, because I believe manhattan distance is a better heuristic compared to misplaced tiles, and can be clearly viewed at solutions in deep depths. 
Let's just take a look at the values and numbers obtained from running all three searches on the 8 puzzle with the following sequence:

1 2 3 <br/>
4 _ 6 <br/>
7 5 8 <br/>

1. **Uniform cost search:**
      * _Goal_ = found
      * _Nodes expanded_ = 9
      * _Max number of nodes in queue_ = 8
2. **A\* with misplaced heuristic:**
      * _Goal_ = found
      * _Nodes expanded_ = 2
      * _Max number of nodes in queue_ = 5
3. **A\* with manhattan distance:**
      * _Goal_ = found
      * _Nodes expanded_ = 2
      * _Max number of nodes in queue_ = 5

From this data it might be hard to see the difference amongst all three, but it shows a nice feature I mentioned before, where some heuristic allows for a better algorithm, in that less nodes are expanded and the queue has to hold fewer nodes as well. 
With this, I can confidentially say that an algorithm with some heuristic is always better, in terms of nodes expanded and nodes held in a queue, than an algorithm with no heuristic. 
But let's take another look at another random puzzle with the following sequence:

1 _ 2 <br/>
3 6 7 <br/>
4 5 8 <br/>

1. **Uniform cost search:**
    * _Goal_ = found
    * _Nodes expanded_ = 37847  
    * _Max number of nodes in queue_ = 26482
2. **A\* with misplaced heuristic:**
    * _Goal_ = found
    * _Nodes expanded_ = 1405
    * _Max number of nodes in queue_ = 958
3. **A\* with manhattan distance:**
    * _Goal_ = found
    * _Nodes expanded_ = 207
    * _Max number of nodes in queue_ = 151

With this data, it's clear to see how the difference amongst all three are starting to be made, and I can confidently say that an algorithm with a good heuristic is always better, in terms of nodes expanded and number of nudes in queue, than an algorithm with just any heuristic. 
When I ran this puzzle though, although it only took a couple of seconds, the uniform cost search was a lot faster than the A* with heuristics. 
It's safe to say that if you are looking to just find any solution, uniform cost search would be the way to go, but if you want a good path, an optimal solution to your problem, then the first thing to consider is if you have a good heuristic or not, as it makes a huge difference on the run time and quality of the solution.
