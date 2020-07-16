#pragma once
#include"Map.h"

class Astar
{

private:
	Map& M;
	const std::list<Pos> delta = std::list<Pos>({ Pos(1,0),Pos(-1,0),Pos(0,1),Pos(0,-1),Pos(1,1),Pos(1,-1),Pos(-1,1),Pos(-1,-1) });

	Pos activePos;

	std::list<Pos> open;
	std::unordered_set<Pos> closed;
	bool solved=false;
	std::list<Pos> solution;


	auto GetMin();

	void ApplySolution();

	std::list<Pos> GetNeighbours(const Pos& pos);


public:
	Astar(Map& map);


	std::list<Pos>& GetOpen();
	std::list<Pos> GetOpen() const;


	std::unordered_set<Pos>& GetClosed();
	std::unordered_set<Pos> GetClosed() const;

	std::list<Pos>& GetSolution();
	std::list<Pos> GetSolution() const;

	Map& GetMap();
	Map GetMap() const;

	Pos ActivePosition();

	bool isSolved() const;

	void SolveStep();

	std::list<Pos> Solve();

	void Initialize(const Pos& i, const Pos& f);


	void setDestination(const Pos& f);

	void setOrigin(const Pos& i);

	void RESET()
	{
		solution.clear();
		solved=false;
		open.clear();
		closed.clear();

		if(M.isInitialized())
		{
			activePos=M.Origin();
			open.push_back(activePos);
		}
		else
		{
			activePos=Pos();
		}
	}

	float PathLength();
};