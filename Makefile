all:
	g++ src/astar.cpp src/util.cpp src/heuristic.cpp src/search.cpp -o bin/astar.out

clean:
	rm bin/astar.out