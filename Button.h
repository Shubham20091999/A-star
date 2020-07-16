#pragma once
#include<SFML/Graphics.hpp>

class Button
{
public:
	enum class ButtonStates { idle, hover, pressedLeft, pressedRight };
	ButtonStates buttonstate;

	std::string id;
	sf::RectangleShape shape;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

	sf::Sprite icon;
	bool isIcon = false;

	sf::Vector2f pos;

	bool isActive = true;
public:
	Button(sf::RectangleShape shape, const std::string& id = "", const sf::Color& hoverColor = sf::Color(150, 150, 150), const sf::Color& activeColor = sf::Color(75, 75, 75));

	~Button();

	Button(const Button& x) = default;

	void setPosition(const sf::Vector2f& p);

	sf::Vector2f getPosition() const;

	void setSprite(const sf::Texture& texture, float scale);


	void update(const sf::Vector2f& mousePos);


	bool isPressed_Left();

	bool isPressed_Right();


	void render(sf::RenderTarget& window, bool active = true);


	void setActive(const bool& active);

	void operator=(const Button& o);

};