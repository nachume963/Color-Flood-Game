#include "Object.h"


Object::Object(sf::Vector2f pos, sf::Vector2f size)
	:m_who_owns(random)
{
	//Sets the shape of the object
	m_shape.setPointCount(4);
	m_shape.setPoint(0, sf::Vector2f(0, 0));
	m_shape.setPoint(1, sf::Vector2f(size.x, 0));
	m_shape.setPoint(2, size);
	m_shape.setPoint(3, sf::Vector2f(0, size.y));

	//set the position of the object
	m_shape.setPosition(pos);
	m_shape.rotate((float)45);

	//Design object
	m_shape.setFillColor(randomColor());
	m_shape.setOutlineColor(sf::Color::Black);
	m_shape.setOutlineThickness(1);
}
Object::~Object()
{
}


void Object::draw(sf::RenderWindow & window) const
{
	window.draw(m_shape);
}

sf::FloatRect Object::getObjectGlobalBounds()
{
	return m_shape.getGlobalBounds();
}
sf::ConvexShape & Object::getShape()
{
	return m_shape;
}
void Object::setWhoOwns(int wo)
{
	m_who_owns = wo;
}
int Object::getWhoOwns()
{
	return m_who_owns;
}
std::vector<std::shared_ptr<Object>> Object::getNeighbors()
{
	return m_neighbors;
}
sf::Color Object::getShapeColor()
{
	return m_shape.getFillColor();
}
void Object::setShapeColor(sf::Color color)
{
	m_shape.setFillColor(color);
}

void Object::addNeighbor(std::shared_ptr<Object> Neighbor)
{
	m_neighbors.push_back(Neighbor);
}

sf::Color Object::randomColor()
{
	int c = rand() % 6;

	//Randomly selects color
	switch (colors(c)) {
	case Yellow:
		return sf::Color::Yellow;
	case Red:
		return sf::Color::Red;
	case Green:
		return sf::Color::Green;
	case Cyan:
		return sf::Color::Cyan;
	case Blue:
		return sf::Color::Blue;
	case Magenta:
		return sf::Color::Magenta;
	case White:
		return sf::Color::White;
	case Black:
		return sf::Color::Black;
		break;
	}
}
