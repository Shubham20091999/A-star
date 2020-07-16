#include<iostream>
#include"Visualization.h"

#define print(x) std::cout<<x<<"\n";
#define printC(x) for(auto c:x){std::cout<<c<<" ";} std::cout<<"\n";

int main()
{
	//To input height
	unsigned int h = 0;
	std::cout << "Input Height of the Map(unsigned int): ";
	while (h < 1)
	{
		std::cin >> h;
		if (h < 1)
			print("Invalid");
		std::cout << "\n";
	}

	//To input width
	unsigned int w = 0;
	std::cout << "Input Width of the Map(unsigned int): ";
	while (w < 1)
	{
		std::cin >> w;
		if (w < 1)
			print("Invalid");
		std::cout << "\n";
	}

	Map map = Map(h, w);/*(10,17)*/

	//Setup for heuristic engine
	unsigned int t = 3;
	std::cout << "Input Heuristic of the Map\n0: Euclidean\n1: Manhattan\n2: Modified Manhattan\n";
	while (t < 0 || t>2)
	{
		std::cin >> t;

		if (t == 0)
			map.setHeuristic(Map::Heuristic::Euclidean);
		else if (t == 1)
			map.setHeuristic(Map::Heuristic::Manhattan);
		else if (t == 2)
			map.setHeuristic(Map::Heuristic::ModifiedManhattan);
		else
			print("Invalid")

		std::cout << "\n";
	}
	//Starting Astar
	Astar A(map);

	Viz::Visualize(A);

	std::cin.get();
}