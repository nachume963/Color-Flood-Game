#include "ColorButton.h"
#include "Controller.h"


ColorButton::ColorButton(sf::Vector2f pos, sf::Color color)
	:Button(pos, SIZE_BUTTON, "EmptySquare.png"), m_color(color)
{
	//set color
	m_button.setColor(color);
}
ColorButton::~ColorButton()
{
}

void ColorButton::click(Controller & controller)
{
	controller.ChangesColor(m_color);
}
