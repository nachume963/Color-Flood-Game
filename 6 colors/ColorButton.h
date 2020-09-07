#pragma once
#include "Button.h"

class ColorButton :	public Button
{
public:
	ColorButton(sf::Vector2f pos, sf::Color color);
	~ColorButton();

	virtual void click(Controller & controller) override;

private:
	sf::Color m_color;
};

