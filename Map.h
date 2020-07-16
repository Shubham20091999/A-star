#pragma once
#include<iostream>
#include<unordered_set>
#include<algorithm>
#include<list>

class Pos
{
public:
	unsigned int m;
	unsigned int n;

	Pos();

	Pos(unsigned int _m, unsigned int _n);

	Pos(const Pos& rhs);

	Pos(Pos&& rhs) noexcept;

	bool operator ==(const Pos& alt) const;

	void operator=(const Pos& rhs);

	friend std::ostream& operator<< (std::ostream& out, const Pos& obj);
};

namespace std
{
	template<>
	struct hash<Pos>
	{
		size_t operator()(const Pos& obj) const
		{
			return hash<unsigned int>()(obj.m * 50 + obj.n);
		}
	};
}

class Site
{
public:
	float fscore;
	float gscore;
	Pos parent;

	Site();
	Site(float f,float g,float h, const Pos& p);
};


class Map
{
public:
	enum class Heuristic { Euclidean, Manhattan, ModifiedManhattan };

private:
	unsigned int h;
	unsigned int w;

	std::unordered_set<Pos> blockade;//check//unordered List
	std::vector<Site> map;

	bool isfpos=false;
	Pos fpos;
	bool isipos=false;
	Pos ipos;
	//Pos cpos;
	Heuristic type = Heuristic::Euclidean;

public:

	Map(unsigned int _h, unsigned int _w);

	void SetDestination(const Pos& _f);
	void SetOrigin(const Pos& _i);

	void SetBlockage(const std::unordered_set<Pos>& _b);

	void AddBlockade(const Pos& b);

	Pos Origin() const;
	Pos& Origin();

	Pos Destination() const;
	Pos& Destination();


	bool isInitialized();
	
	Site operator()(const Pos& p) const;
	Site& operator()(const Pos& p);

	Pos GetMemLoc(unsigned int l);
	unsigned int GetPos(const Pos& pos) const;

	//Pos CurrentPosition() const;

	static bool isDiagonal(const Pos& pos, const Pos& cpos);

	bool isBlocked(const Pos& pos,const Pos* cpos=nullptr) const;

	float Distance(const Pos& a, const Pos& b);
	static float Distance(const Pos& a, const Pos& b, enum Map::Heuristic h);
	static float EuclideanDistance(const Pos& a, const Pos& b);
	static float ManhattanDistance(const Pos& a,const Pos& b);
	static float M_ManhattanDistance(const Pos& a, const Pos& b);

	unsigned int height();
	unsigned int width();

	//friend class Viz;
	//friend class Setup;
	//friend class Astar;

	void RESET()
	{
		blockade.clear();
		ipos=Pos();
		fpos=Pos();
		isfpos=false;
		isipos=false;
	}

	void setHeuristic(enum Map::Heuristic h);
	enum Map::Heuristic Heuristic();

};