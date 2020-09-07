#pragma once
#include "Constants.h"

class GameBoard;

class Object
{
public:
	Object(sf::Vector2f pos, sf::Vector2f size);
	~Object();

	//draw
	virtual void draw(sf::RenderWindow & window) const;
	//Returns the blocking square of an object
	sf::FloatRect getObjectGlobalBounds();
	
	//get - set
	sf::ConvexShape & getShape();
	
	void setWhoOwns(int wo);
	int getWhoOwns();
	
	std::vector<std::shared_ptr<Object>> getNeighbors();
	sf::Color getShapeColor();
	
	void setShapeColor(sf::Color color);
	
	//Adds neighbor to the neighbors list
	void addNeighbor(std::shared_ptr<Object> Neighbor);
	
protected:
	//Selects a color for each object in a random way
	sf::Color randomColor();
	
	//members
	sf::ConvexShape m_shape;
	std::vector<std::shared_ptr<Object>> m_neighbors;
	int m_who_owns;
};

