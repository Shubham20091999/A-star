#include"TextBox.h"

TextBox::TextBox(const std::string& m) :
	message(m)
{
	font.loadFromFile("Assets/Font.ttf");
	text = (sf::Text(m, font, txtsize));
	sf::FloatRect backgroundRect = text.getLocalBounds();
	bg = sf::RectangleShape(sf::Vector2f(backgroundRect.width, backgroundRect.height + 7 * txtsize / 20));
	bg.setOutlineThickness(3);
	bg.setFillColor(sf::Color(0, 0, 0, 200));
	bg.setOutlineColor(sf::Color(0, 0, 0, 200));
}

void TextBox::setOrigin(float x, float y)
{
	text.setOrigin(x * text.getLocalBounds().width, y * text.getLocalBounds().height);
}

void TextBox::setPosition(float x, float y)
{
	text.setPosition(x, y);
}

void TextBox::render(sf::RenderWindow& w)
{
	w.draw(bg, text.getTransform());
	w.draw(text);
}

void TextBox::setMessage(const std::string& c)
{
	text.setString(c);
	sf::FloatRect backgroundRect = text.getLocalBounds();
	bg.setSize(sf::Vector2f(backgroundRect.width, backgroundRect.height + 7 * txtsize / 20));
}