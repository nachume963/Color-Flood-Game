#pragma once
#include "Constants.h"

class Controller;

class Button
{
public:
	Button(sf::Vector2f pos, sf::Vector2f size, std::string name_file);
	virtual ~Button();

	//draw
	void draw(sf::RenderWindow & window) const;

	//get
	sf::FloatRect getObjectGlobalBounds();
	
	//Pure virtual function
	virtual void click(Controller & controller) = 0;

protected:
	//members
	sf::Sprite m_button;
	sf::Texture T;
};

