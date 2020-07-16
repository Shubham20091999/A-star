#include"Map.h"

//Pos
Pos::Pos():
	m(-1),n(-1)
	{}

Pos::Pos(unsigned int _m, unsigned int _n) : m(_m), n(_n)
{
	if (_m < 0 || _n < 0)
		throw(std::exception("Position cannot be nagative"));
}

Pos::Pos(const Pos& rhs)=default;

Pos::Pos(Pos&& rhs) noexcept =default;


bool Pos::operator ==(const Pos& alt) const
{
	if (m == alt.m && n == alt.n)
		return true;
	return false;
}

void Pos::operator=(const Pos& rhs)
{
	m = rhs.m;
	n = rhs.n;
}

std::ostream& operator<< (std::ostream& out, const Pos& obj)
{
	out << '(' << obj.m << ',' << obj.n << ')';
	return out;
}

//Site
Site::Site() :
	fscore(INFINITY), gscore(INFINITY), parent(Pos()) {}

Site::Site(float f, float g, float h, const Pos& p) :
	fscore(f), gscore(g), parent(p) {}

//Map
Map::Map(unsigned int _h, unsigned int _w) :
	h(_h), w(_w), map(std::vector<Site>(_h* _w, Site())) {}

void Map::SetDestination(const Pos& f) 
{ 
	if(f.m>=h || f.n>=w)
		throw(std::exception("Destination out of Bound"));
	isfpos=true;
	fpos = f; 
}

void Map::SetOrigin(const Pos& i)
{
	if (i.m >= h || i.n >= w)
		throw(std::exception("Origin out of Bound"));
	isipos = true;
	ipos = i;
	(*this)(ipos).gscore = 0;
	(*this)(ipos).fscore = (*this)(ipos).gscore + Map::Distance(ipos, fpos,type);
}

void Map::SetBlockage(const std::unordered_set<Pos>& _b)
{
	blockade = _b;
}

void Map::AddBlockade(const Pos& b)
{
	blockade.emplace(b);
}

unsigned int Map::GetPos(const Pos& pos) const
{
	if (pos.m >= h or pos.n >= w or pos.m < 0 or pos.n < 0)
		return NULL;
	return pos.m * w + pos.n;
}

Pos Map::GetMemLoc(unsigned int l)
{
	return Pos((unsigned int)l / w, l % w);
}

Site& Map::operator()(const Pos& p)
{
	return map[GetPos(p)];
}

Site Map::operator()(const Pos& p) const
{
	return map[GetPos(p)];
}

bool Map::isDiagonal(const Pos& pos, const Pos& cpos)
{
	if (pos.m - cpos.m == 0 || pos.n - cpos.n == 0)
		return false;
	return true;
}

bool Map::isBlocked(const Pos& pos, const Pos* cpos) const
{
	if (cpos)
	{
		if (Map::isDiagonal(pos, *cpos))
		{
			if (isBlocked(Pos(pos.m, cpos->n)) && isBlocked(Pos(cpos->m, pos.n)))
				return true;
		}
	}

	if (blockade.count(pos) != 0 or pos.m >= h or pos.n >= w or pos.m < 0 or pos.n < 0)
		return true;
	return false;
}

float Map::EuclideanDistance(const Pos& a, const Pos& b)
{
	return ((powf(powf((float)(a.m) - (float)b.m, 2.0f) + powf((float)(a.n) - (float)b.n, 2.0f), 0.5f)));
}

float Map::ManhattanDistance(const Pos& a, const Pos& b)
{
	return abs(float(a.m) - float(b.m)) + abs(float(a.n) - float(b.n));
}

float Map::M_ManhattanDistance(const Pos& a, const Pos& b)
{
	float m = abs(float(a.m) - float(b.m));
	float n = abs(float(a.n) - float(b.n));

	float min = m;
	float max = n;

	if (min > max)
	{
		min = n;
		max = m;
	}
	return min*float(sqrt(2))+(max-min);
}

float Map::Distance(const Pos& a, const Pos& b,enum Map::Heuristic h)
{
	if (h == Heuristic::Manhattan)
		return Map::ManhattanDistance(a, b);
	if (h == Heuristic::ModifiedManhattan)
		return Map::M_ManhattanDistance(a, b);

	return Map::EuclideanDistance(a, b);
}

float Map::Distance(const Pos& a,const Pos& b)
{
	if (type == Heuristic::Manhattan)
			return Map::ManhattanDistance(a, b);
	if (type == Heuristic::ModifiedManhattan)
			return Map::M_ManhattanDistance(a, b);

	return Map::EuclideanDistance(a, b);
}

Pos Map::Origin() const
{
	return ipos;
}

Pos& Map::Origin()
{
	return ipos;
}

Pos Map::Destination() const
{
	return fpos;
}

Pos& Map::Destination()
{
	return fpos;
}


bool Map::isInitialized()
{
	return isfpos*isipos;
}

unsigned int Map::height()
{
	return h;
}

unsigned int Map::width()
{
	return w;
}

void Map::setHeuristic(enum class Map::Heuristic h)
{
	if(isipos)
		throw(std::exception("Heuristic must be set before setting the initial position"));
	type=h;
}

enum class Map::Heuristic Map::Heuristic()
{
	return type;
}