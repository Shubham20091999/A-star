#pragma once
#include<SFML/Graphics.hpp>

class TextBox
{
private:
	std::string message;
	unsigned int txtsize = 20;
	sf::Color textColor=sf::Color::White;
	sf::RectangleShape bg;


	sf::Text text;
	sf::Font font;

public:
	TextBox()=delete;

	TextBox(const std::string& m);

	void setOrigin(float x,float y);

	void setPosition(float x,float y);

	void render(sf::RenderWindow& w);

	void setMessage(const std::string& c);
};