#pragma once
#include "Constants.h"

#include "Button.h"

class Menu
{
public:
	Menu();
	~Menu();

	//draw
	void draw(sf::RenderWindow & window) const;

	//Function that activates the function by pressing the button
	void click(Controller & controller, sf::Vector2f mouseButtonPos);

private:
	//Vector of pointers to buttons
	std::vector <std::unique_ptr<Button>> m_buttons;
};

