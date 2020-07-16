#pragma once
#include"Button.h"

Button::Button(sf::RectangleShape shape, const std::string& id,
	const sf::Color& hoverColor, const sf::Color& activeColor) :
	shape(shape),
	idleColor(shape.getFillColor()),
	hoverColor(hoverColor),
	activeColor(activeColor),
	id(id)
{
	buttonstate = ButtonStates::idle;
}

Button::~Button() = default;

void Button::update(const sf::Vector2f & mousePos)
{
	if (isActive)
	{
		if (shape.getGlobalBounds().contains(mousePos))
		{
			buttonstate = ButtonStates::hover;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				shape.setFillColor(activeColor);
				buttonstate = ButtonStates::pressedLeft;
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				shape.setFillColor(activeColor);
				buttonstate = ButtonStates::pressedRight;
			}
		}
		else
		{
			shape.setFillColor(idleColor);
			buttonstate = ButtonStates::idle;
		}

		if (buttonstate == ButtonStates::hover)
			shape.setFillColor(hoverColor);
	}
	else
	{
		buttonstate = ButtonStates::idle;
		icon.setColor(sf::Color(50, 50, 50));
	}
}

bool Button::isPressed_Left()
{
	return buttonstate == ButtonStates::pressedLeft;
}

bool Button::isPressed_Right()
{
	return buttonstate == ButtonStates::pressedRight;
}

void Button::render(sf::RenderTarget & window, bool active)
{
	if (active)
		window.draw(shape);
	else
	{
		shape.setFillColor(this->activeColor);
		window.draw(shape);
	}
	if (isIcon)
		window.draw(icon);
}

void Button::setPosition(const sf::Vector2f & p)
{
	shape.setPosition(p);
	if (isIcon)
		icon.setPosition(p.x + shape.getSize().x / 2 - icon.getScale().x * icon.getTexture()->getSize().x / 2, p.y + shape.getSize().y / 2 - icon.getScale().y * (icon.getTexture())->getSize().y / 2);
}

sf::Vector2f Button::getPosition() const
{
	return shape.getPosition();
}

void Button::setSprite(const sf::Texture & texture, float scale)
{
	icon.setTexture(texture);
	icon.setScale(scale, scale);
	isIcon = true;
}

void Button::setActive(const bool& active)
{

	isActive = active;

	if (isActive)
		icon.setColor(sf::Color(255, 255, 255));
	else
		icon.setColor(sf::Color(50, 50, 50));
}

void Button::operator=(const Button & o)
{
	shape = o.shape;

	idleColor = o.idleColor;
	hoverColor = o.hoverColor;
	activeColor = activeColor;

	icon = o.icon;

	pos = o.pos;

	id = o.id;
	isIcon = o.isIcon;
}