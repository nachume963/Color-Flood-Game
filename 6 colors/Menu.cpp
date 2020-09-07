#include "Menu.h"

#include "Exit.h"
#include "ResetGame.h"
#include "ColorButton.h"


Menu::Menu()
{
	//constructor. Initializing 8 buttons:
	//Exit
	m_buttons.push_back(std::make_unique<Exit>());
	//Reset level
	m_buttons.push_back(std::make_unique<ResetGame>());
	//color buttons
	m_buttons.push_back(std::make_unique<ColorButton>(sf::Vector2f(50.0, 120.0), sf::Color::Blue));
	m_buttons.push_back(std::make_unique<ColorButton>(sf::Vector2f(50.0, 240.0), sf::Color::Cyan));
	m_buttons.push_back(std::make_unique<ColorButton>(sf::Vector2f(50.0, 360.0), sf::Color::Green));
	m_buttons.push_back(std::make_unique<ColorButton>(sf::Vector2f(50.0, 480.0), sf::Color::Magenta));
	m_buttons.push_back(std::make_unique<ColorButton>(sf::Vector2f(50.0, 600.0), sf::Color::Red));
	m_buttons.push_back(std::make_unique<ColorButton>(sf::Vector2f(50.0, 720.0), sf::Color::Yellow));
}
Menu::~Menu()
{
}


void Menu::draw(sf::RenderWindow & window) const
{
	for (int i = 0; i < m_buttons.size(); i++)
		m_buttons[i]->draw(window);
}

void Menu::click(Controller & controller, sf::Vector2f mouseButtonPos)
{
	//Calls the relevant function using polymorphism
	for (int i = 0; i < m_buttons.size(); i++)
		if(m_buttons[i]->getObjectGlobalBounds().contains(mouseButtonPos))
			m_buttons[i]->click(controller);
}
