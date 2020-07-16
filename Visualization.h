#pragma once
#include"Astar.h"
#include"Map.h"
#include"Button.h"
#include"TextBox.h"

static TextBox text("");

class Viz
{
public:
	sf::RenderWindow& window;
	Map& M;

	const float init_offsetx = 80;
	const float init_offsety = 5;

	const float delta = 2.5;

	const float defsize = 75.0f;
	float size = defsize;//limit 20
	float scale = 1.0f;

	sf::Texture iposT;
	sf::Texture fposT;
	sf::Texture closeT;
	sf::Texture clearT;

	Button closeB;
	Button clearB;

public:
	sf::RectangleShape stockR;
	sf::RectangleShape openR;
	sf::RectangleShape closeR;
	sf::RectangleShape pathR;
	sf::RectangleShape blockR;
	sf::RectangleShape cposR;

	sf::Sprite iposS;
	sf::Sprite fposS;

	Viz() = delete;

	Viz(sf::RenderWindow& win, Map& M);

	static sf::RectangleShape GetRect(const sf::Color& color, const Viz& v, bool scale = true);

	void MapInit();

	void UpdateScale();

	void ScaleUp(float s);

	void Viz_Astar(Astar& A);

	void Viz_End(Astar& A);

	static void Visualize(Astar& A, float vfps = 24);
};

class Setup
{
	Viz& V;

	Button stockB;
	Button MblockB;
	Button MdestinationB;
	Button MoriginB;

	Button blockB;
	Button destinationB;
	Button originB;
	Button destroyB;
	Button nextB;

	sf::Texture blockT;
	sf::Texture destinationT;
	sf::Texture originT;
	sf::Texture nextT;
	sf::Texture destroyT;

	std::list<Button> Sites;

	enum class States { None, SetOrigin, SetDestination, SetBlock,DestroyBlock };

	States currentState;

	Setup() = delete;

	void ClearScreen();
	void CheckInputs();
	bool End(Astar& A);

public:
	Setup(Viz& V);
	bool Init(Astar& A);
};




