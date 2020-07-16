#include"Astar.h"

Astar::Astar(Map& map)
	:M(map)
	{
	if (map.isInitialized())
		Initialize(map.Origin(),map.Destination());
	}

auto Astar::GetMin()
{
	float min = M(*open.begin()).fscore;
	auto ret = open.begin();

	for (auto e = open.begin(); e != open.end(); e++)
	{
		if (M(*(e)).fscore < min)
		{
			min = M(*e).fscore;
			ret = e;
		}
	}
	return ret;
}

void Astar::ApplySolution()
{
	Pos p = M.Destination();
	while (true)
	{
		if (p == M.Origin())
			break;
		solution.emplace_front(p);
		p = M(p).parent;
	}
}

std::list<Pos> Astar::GetNeighbours(const Pos& pos)
{
	std::list<Pos> ret;
	for (auto d = Astar::delta.begin(); d != Astar::delta.end(); d++)
	{
		Pos npos(pos.m + (*d).m, pos.n + (*d).n);
		if (!M.isBlocked(npos, &activePos))
			ret.emplace_front(std::move(npos));
	}

	return ret;
}


std::list<Pos>& Astar::GetOpen()
{
	return open;
}

std::list<Pos> Astar::GetOpen() const
{
	return open;
}


std::unordered_set<Pos>& Astar::GetClosed()
{
	return closed;
}

std::unordered_set<Pos> Astar::GetClosed() const
{
	return closed;
}



std::list<Pos>& Astar::GetSolution()
{
	if (solved)
		return solution;
	throw(std::exception("Map Not Solved Yet"));
}

std::list<Pos> Astar::GetSolution() const
{
	if (solved)
		return solution;
	throw(std::exception("Map Not Solved Yet"));
}	


Map& Astar::GetMap()
{
	return M;
}

Map Astar::GetMap() const
{
	return M;
}


bool Astar::isSolved() const
{
	return solved;
}

void Astar::SolveStep()
{
	if (!M.isInitialized())
		throw("Map not Initilized");

	if (open.empty())
		throw(std::exception("Path does not Exist"));

	auto minloc = GetMin();

	activePos = *minloc;
	open.erase(minloc);
	closed.insert(activePos);

	if (activePos == M.Destination())
	{
		solved = true;
		ApplySolution();
		return;
	}

	auto neighbours = GetNeighbours(activePos);

	for (auto npos : neighbours)
	{
		if (closed.count(npos) != 0)
			continue;
		float n_gscore = Map::Distance(npos, activePos,M.Heuristic()) + M(activePos).gscore;
		float n_fscore = n_gscore + Map::Distance(npos, M.Destination(),M.Heuristic());

		bool inOpen = (std::find(open.begin(), open.end(), npos) != open.end());

		if (M(npos).fscore > n_fscore || !inOpen)
		{
			M(npos).fscore = n_fscore;
			M(npos).gscore = n_gscore;
			M(npos).parent = activePos;

			if (!inOpen)
				open.push_front(npos);

		}
	}
}

std::list<Pos> Astar::Solve()
{
	if(!M.isInitialized())
		throw("Map not Initilized");

	while (!solved)
	{
		SolveStep();
	}
	return solution;
}

Pos Astar::ActivePosition()
{
	return activePos;
}

void Astar::Initialize(const Pos& i,const Pos& f)
{
	M.SetOrigin(i);
	M.SetDestination(f);

	open.push_front(i);
}


void Astar::setDestination(const Pos& f)
{
	M.SetDestination(f);
}

void Astar::setOrigin(const Pos& i)
{
	M.SetOrigin(i);
	open.clear();
	open.push_front(i);
}

float Astar::PathLength()
{
	if(!solved)
		throw(std::exception("Map Not Solved Yet"));
	float ans=Map::EuclideanDistance(M.Origin(),*solution.begin());
	for (auto e = solution.begin(); std::next(e)!= solution.end(); e++)
	{
		ans+=Map::EuclideanDistance(*e,*std::next(e));
	}
	return ans;
}