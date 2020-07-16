#include"Visualization.h"

//Vizualization
Viz::Viz(sf::RenderWindow& win, Map& M) :
	window(win), M(M),
	closeB(Button(Viz::GetRect(sf::Color(50, 50, 50), *this, false), "closeB", sf::Color(255, 0, 0), sf::Color(255, 50, 50))),
	clearB(Button(Viz::GetRect(sf::Color(50, 50, 50), *this, false), "closeB", sf::Color(255, 0, 0), sf::Color(255, 50, 50)))
{
	if ((float)M.width() / 16.7f > (float)M.height() / 9.9f)
	{
		if (M.width() > 16.7f)
			scale = 16.7f / (float)M.width();
	}
	else
	{
		if (M.height() > 9.9)
			scale = 9.9f / (float)M.height();
	}

	size = scale * defsize;

	closeT.loadFromFile("Assets/Close.png");
	closeT.setSmooth(true);
	closeB.setSprite(closeT, 0.8f);
	closeB.setPosition(sf::Vector2f(delta, delta + 685));

	clearT.loadFromFile("Assets/Clear.png");
	clearT.setSmooth(true);
	clearB.setSprite(clearT, 0.8f);
	clearB.setPosition(sf::Vector2f(delta, delta + 600));

	stockR = Viz::GetRect(sf::Color(125, 125, 125), *this);
	openR = Viz::GetRect(sf::Color::Blue, *this);
	closeR = Viz::GetRect(sf::Color::Red, *this);
	pathR = Viz::GetRect(sf::Color::Magenta, *this);
	blockR = Viz::GetRect(sf::Color(50, 50, 50), *this);
	cposR = Viz::GetRect(sf::Color::Green, *this);

	iposT.loadFromFile("Assets/Origin.png");
	fposT.loadFromFile("Assets/Destination.png");
	iposT.setSmooth(true);
	fposT.setSmooth(true);

	iposS = sf::Sprite(iposT);
	fposS = sf::Sprite(fposT);

	iposS.setScale(0.8f * size / defsize, 0.8f * size / defsize);
	fposS.setScale(0.8f * size / defsize, 0.8f * size / defsize);
}

sf::RectangleShape Viz::GetRect(const sf::Color& color, const Viz& v, bool scale)
{
	sf::RectangleShape shape;
	if (scale)
	{
		shape.setSize(sf::Vector2f(v.scale * v.defsize, v.scale * v.defsize));
		shape.setOutlineThickness(-v.delta * v.scale);
	}
	else
	{
		shape.setSize(sf::Vector2f(v.defsize, v.defsize));
		shape.setOutlineThickness(-v.delta);
	}

	shape.setOutlineColor(sf::Color::Black);
	shape.setFillColor(color);

	return shape;
}

void Viz::MapInit()
{
	sf::RectangleShape rect;

	for (unsigned int i = 0; i < M.height(); i++)
	{
		for (unsigned int j = 0; j < M.width(); j++)
		{
			if (M.isBlocked(Pos(i, j)))
				rect = blockR;
			else
				rect = stockR;

			rect.setPosition(sf::Vector2f(init_offsetx + j * size, init_offsety + i * size));

			window.draw(rect);
		}
	}
	window.draw(iposS);
	window.draw(fposS);
}

void Viz::UpdateScale()
{
	stockR = Viz::GetRect(sf::Color::White, *this);
	openR = Viz::GetRect(sf::Color::Blue, *this);
	closeR = Viz::GetRect(sf::Color::Red, *this);
	pathR = Viz::GetRect(sf::Color::Magenta, *this);
	blockR = Viz::GetRect(sf::Color(50, 50, 50), *this);
	cposR = Viz::GetRect(sf::Color::Green, *this);

	iposS.setScale(0.8f * scale, 0.8f * scale);
	fposS.setScale(0.8f * scale, 0.8f * scale);

	iposS.setPosition(init_offsetx + M.Origin().n * size + size / 2, init_offsety + M.Origin().m * size + size / 2);
	fposS.setPosition(init_offsetx + M.Destination().n * size + size / 2, init_offsety + M.Destination().m * size + size / 2);

}

void Viz::ScaleUp(float s)
{
	scale += 0.05f * s;
	if (scale < 0.2667f)
		scale = 0.2667f;

	size = defsize * scale;
	UpdateScale();
}

void Viz::Viz_Astar(Astar& A)
{
	for (auto c : A.GetClosed())
	{
		closeR.setPosition(sf::Vector2f(init_offsetx + c.n * size, init_offsety + c.m * size));
		window.draw(closeR);
	}

	for (auto c : A.GetOpen())
	{
		openR.setPosition(sf::Vector2f(init_offsetx + c.n * size, init_offsety + c.m * size));
		window.draw(openR);
	}

	cposR.setPosition(init_offsetx + A.ActivePosition().n * size, init_offsety + A.ActivePosition().m * size);
	window.draw(cposR);

	window.draw(iposS);
	window.draw(fposS);
}

void Viz::Viz_End(Astar& A)
{
	pathR.setPosition(sf::Vector2f(init_offsetx + M.Origin().n * size, init_offsety + M.Origin().m * size));
	window.draw(pathR);
	for (auto c : A.GetSolution())
	{
		pathR.setPosition(sf::Vector2f(init_offsetx + c.n * size, init_offsety + c.m * size));
		window.draw(pathR);
	}

	window.draw(iposS);
	window.draw(fposS);
}



//Setup
Setup::Setup(Viz& V)
	:V(V),
	stockB(Button(V.stockR, "stockB")),
	MblockB(Button(V.blockR, "MblockB")),
	MdestinationB(Button(V.stockR, "MdestinationB", sf::Color::Transparent, sf::Color::Transparent)),
	MoriginB(Button(V.stockR, "MoriginB", sf::Color::Transparent, sf::Color::Transparent)),
	blockB(Button(Viz::GetRect(sf::Color(50, 50, 50), V, false), "blockB")),
	destinationB(Button(Viz::GetRect(sf::Color(50, 50, 50), V, false), "destinationB")),
	destroyB(Button(Viz::GetRect(sf::Color(50, 50, 50),V,false),"destroyB", sf::Color(255, 0, 0), sf::Color(255, 50, 50))),
	originB(Button(Viz::GetRect(sf::Color(50, 50, 50), V, false), "originB")),
	nextB(Button(Viz::GetRect(sf::Color(50, 50, 50), V, false), "nextB", sf::Color(76, 187, 23), sf::Color(11, 102, 35))),
	currentState(States::None)
{
	blockT.loadFromFile("Assets/Block.png");
	destinationT.loadFromFile("Assets/Destination.png");
	originT.loadFromFile("Assets/Origin.png");
	nextT.loadFromFile("Assets/Next.png");
	destroyT.loadFromFile("Assets/Destroy.png");

	blockT.setSmooth(true);
	destinationT.setSmooth(true);
	originT.setSmooth(true);
	nextT.setSmooth(true);
	destroyT.setSmooth(true);

	MblockB.setSprite(blockT, 0.8f * V.size / V.defsize);
	MdestinationB.setSprite(destinationT, 0.8f * V.size / V.defsize);
	MoriginB.setSprite(originT, 0.8f * V.size / V.defsize);


	originB.setSprite(originT, 0.8f);
	destinationB.setSprite(destinationT, 0.8f);
	blockB.setSprite(blockT, 0.8f);
	nextB.setSprite(nextT, 0.8f);
	destroyB.setSprite(destroyT, 0.8f);


	originB.setPosition(sf::Vector2f(V.delta, V.delta));
	destinationB.setPosition(sf::Vector2f(V.delta, V.delta + 85));
	blockB.setPosition(sf::Vector2f(V.delta, V.delta + 170));
	destroyB.setPosition(sf::Vector2f(V.delta, V.delta + 255));
	nextB.setPosition(sf::Vector2f(V.delta, V.delta + 340));
}

void Setup::ClearScreen()
{
	originB.setActive(true);
	destinationB.setActive(true);

	Sites.clear();

	for (unsigned int i = 0; i < V.M.height(); i++)//check according to upperbound and lower bound
	{
		for (unsigned int j = 0; j < V.M.width(); j++)
		{
			if(V.M.isBlocked(Pos(i,j)))
			{
				MblockB.setPosition(sf::Vector2f(V.init_offsetx + j * V.size, V.init_offsety + i * V.size));
				Sites.push_back(MblockB);
			}
			else if(V.M.Destination()==Pos(i,j))
			{
				MdestinationB.setPosition(sf::Vector2f(V.init_offsetx + j * V.size, V.init_offsety + i * V.size));
				Sites.push_back(MdestinationB);
				destinationB.setActive(false);
			}
			else if (V.M.Origin() == Pos(i, j))
			{
				MoriginB.setPosition(sf::Vector2f(V.init_offsetx + j * V.size, V.init_offsety + i * V.size));
				Sites.push_back(MoriginB);
				originB.setActive(false);
			}
			else
			{
				stockB.setPosition(sf::Vector2f(V.init_offsetx + j * V.size, V.init_offsety + i * V.size));
				Sites.push_back(stockB);
			}
			
		}
	}
	text.setMessage("Psst! Use Right Click to erase anything from the map");
}

void Setup::CheckInputs()
{
	sf::Vector2f mousePos((float)sf::Mouse::getPosition(V.window).x, (float)sf::Mouse::getPosition(V.window).y);

	originB.update(mousePos);
	originB.render(V.window, currentState != States::SetOrigin);
	if (originB.isPressed_Left())
		currentState = States::SetOrigin;

	destinationB.update(mousePos);
	destinationB.render(V.window, currentState != States::SetDestination);
	if (destinationB.isPressed_Left())
		currentState = States::SetDestination;

	blockB.update(mousePos);
	blockB.render(V.window, currentState!= States::SetBlock);
	if (blockB.isPressed_Left())
		currentState = States::SetBlock;

	destroyB.update(mousePos);
	destroyB.render(V.window, currentState != States::DestroyBlock);
	if(destroyB.isPressed_Left())
		currentState=States::DestroyBlock;

	for (auto e = Sites.begin(); e != Sites.end(); e++)
	{
		e->update(mousePos);
		e->render(V.window);
		if (e->isPressed_Left())
		{
			if (e->id == "stockB")
			{
				switch (currentState)
				{
				case States::SetOrigin:
					MoriginB.setPosition(e->getPosition());
					currentState = States::None;
					originB.setActive(false);
					*e = MoriginB;
					break;
				case States::SetDestination:
					MdestinationB.setPosition(e->getPosition());
					currentState = States::None;
					destinationB.setActive(false);
					*e = MdestinationB;
					break;
				case States::SetBlock:
					MblockB.setPosition(e->getPosition());
					*e = MblockB;
					break;
				case States::None:
					break;
				}
			}
			else if (e->id == "MblockB" && currentState == States::DestroyBlock)
			{
				stockB.setPosition(e->getPosition());
				*e = stockB;
			}

		}
		else if (e->isPressed_Right())
		{
			if (e->id == "MoriginB")
			{
				stockB.setPosition(e->getPosition());
				*e = stockB;
				originB.setActive(true);
			}
			else if (e->id == "MdestinationB")
			{
				stockB.setPosition(e->getPosition());
				*e = stockB;
				destinationB.setActive(true);
			}
			else if (e->id == "MblockB")
			{
				stockB.setPosition(e->getPosition());
				*e = stockB;
			}
		}
	}
}

bool Setup::End(Astar& A)
{
	unsigned int pos = 0;
	V.M.RESET();
	bool origin = false;
	bool destination = false;
	for (auto e = Sites.begin(); e != Sites.end(); e++)
	{
		if (e->id == "MblockB")
			V.M.AddBlockade(V.M.GetMemLoc(pos));
		else if (e->id == "MdestinationB")
		{
			A.setDestination(V.M.GetMemLoc(pos));
			destination = true;
		}
		else if (e->id == "MoriginB")
		{
			A.setOrigin(V.M.GetMemLoc(pos));
			origin = true;
		}
		pos++;
	}
	if (!destination || !origin)
	{
		text.setMessage("Origin or Destination does not Exist");
		std::cout << ("Origin or Destination doesnot Exist\n");
	}
	return origin * destination;
}

bool Setup::Init(Astar& A)
{
	ClearScreen();
	while (V.window.isOpen())
	{
		sf::Event event;
		while (V.window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				V.window.close();
		}
		V.window.clear();

		sf::Vector2f mousePos((float)sf::Mouse::getPosition(V.window).x, (float)sf::Mouse::getPosition(V.window).y);

		V.clearB.update(mousePos);
		V.clearB.render(V.window);
		if (V.clearB.isPressed_Left())
		{
			text.setMessage("Setup Reseted");
			std::cout<<("Setup Reseted\n");
			V.M.RESET();
			sf::sleep(sf::seconds(0.1f));
			A.RESET();
			return false;
		}
		nextB.update(mousePos);
		nextB.render(V.window);
		if (nextB.isPressed_Left())
			if (End(A))
			{
				V.iposS.setOrigin((float)V.iposS.getTexture()->getSize().x / 2, (float)V.iposS.getTexture()->getSize().y / 2);
				V.fposS.setOrigin((float)V.fposS.getTexture()->getSize().x / 2, (float)V.fposS.getTexture()->getSize().y / 2);

				V.iposS.setPosition(V.init_offsetx + V.M.Origin().n * V.size + V.size / 2, V.init_offsety + V.M.Origin().m * V.size + V.size / 2);
				V.fposS.setPosition(V.init_offsetx + V.M.Destination().n * V.size + V.size / 2, V.init_offsety + V.M.Destination().m * V.size + V.size / 2);
				V.window.clear();
				return true;
			}

		V.closeB.update(mousePos);
		V.closeB.render(V.window);
		if (V.closeB.isPressed_Left())
		{
			V.window.close();
		}
		CheckInputs();
		text.render(V.window);
		V.window.display();
	}
	return true;
}


//Final
void Viz::Visualize(Astar& A, float vfps)
{
	sf::RenderWindow window(sf::VideoMode(1366, 768), "Astar", sf::Style::Fullscreen | sf::Style::Close);
	window.setFramerateLimit(24);
	float speedScaler = vfps / 24;
	float counter = 1;

	Viz V(window, A.GetMap());
	Setup S(V);
	text.setPosition(75 + 3 * V.delta, 738);
reset:
	window.clear();
	sf::sleep(sf::seconds(0.5f));
	if (!S.Init(A))
		goto reset;
	text.setMessage("Computing Path");

	bool PathExists=true;
	bool PathPrinted=false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseWheelMoved)
			{
				V.ScaleUp((float)event.mouseWheel.delta);
			}
		}

		window.clear();

		sf::Vector2f mousePos((float)sf::Mouse::getPosition(V.window).x, (float)sf::Mouse::getPosition(V.window).y);

		V.closeB.update(mousePos);
		V.closeB.render(V.window);
		if (V.closeB.isPressed_Left())
		{
			V.window.close();
			//exit(0);
		}

		V.clearB.update(mousePos);
		V.clearB.render(V.window);
		if (V.clearB.isPressed_Left())
		{
			text.setMessage("Computations Reseted");
			std::cout << ("Computations Reseted\n");
			A.RESET();
			V.window.clear();
			goto reset;
			break;
		}

		if (!A.isSolved())
		{
			if (counter >= 1)
			{
				if(PathExists)
				{
					try
					{
						A.SolveStep();
					}
					catch (std::exception a)
					{
						text.setMessage(a.what());
						std::cout << a.what()<<"\n";
						PathExists=false;
					}
					counter = 0;
				}
			}
			V.MapInit();
			V.Viz_Astar(A);
			counter += speedScaler;
		}
		else
		{
			V.MapInit();
			V.Viz_End(A);
			if(!PathPrinted)
			{
				text.setMessage(std::string("Path Computed, Path length=")+std::to_string(A.PathLength()));
				PathPrinted=true;
			}
		}
		text.render(window);
		window.display();
	}
}