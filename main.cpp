#include<iostream>
#include"Visualization.h"
#include<string>
#define print(x) std::cout<<x<<"\n";
#define printC(x) for(auto c:x){std::cout<<c<<" ";} std::cout<<"\n";
using namespace std;

bool isNumber(std::string s)
{
	for (unsigned int i = 0; i < s.length(); i++)
		if (isdigit(s[i]) == false)
			return false;

	return true;
}


int main()
{
	//To input height
	std::string hs = "0";
	unsigned int h = 0;
	std::cout << "Input the dimenstions of the Map" << '\n';
	while (h < 1)
	{
		std::cout << "Height: ";
		std::cin >> hs;
		if (isNumber(hs))
		{
			h = stoi(hs);
			if (h < 1)
				print("Invalid");
			if (h >= 40)
				print("Warning: It is prefered if the height is under 40")
				std::cout << "\n";
		}
		else
		{
			print("Invalid");
		}
	}

	//To input width
	std::string ws = "0";
	unsigned int w = 0;

	while (w < 1)
	{
		std::cout << "Width: ";
		std::cin >> ws;
		if (isNumber(ws))
		{
			w = stoi(ws);
			if (w < 1)
				print("Invalid");
			if (w >= 70)
				print("Warning: It is prefered if the width is under 70")
				std::cout << "\n";
		}
		else
		{
			print("Invalid");
		}
	}

	Map map = Map(h, w);/*(10,17)*/

	//Setup for heuristic engine
	std::string ts = "";
	unsigned int t = 3;
	std::cout << "Input Heuristic of the Map\n0: Euclidean\n1: Manhattan\n2: Modified Manhattan\n";
	while (t < 0 || t>2)
	{
		std::cin >> ts;
		if (isNumber(ts))
		{
			t=stoi(ts);
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
		else
		{
			print("Invalid");
		}
	}
	//Starting Astar
	Astar A(map);

	Viz::Visualize(A);

	std::cin.get();
}