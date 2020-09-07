#pragma once
#include "Constants.h"

#include "Object.h"

class GameBoard
{
public:
	GameBoard();
	~GameBoard();

	//draw the objects
	void draw(sf::RenderWindow & window) const;
	//new game
	void resetGame();
	
	//Replaces the colors in the board and updates the data
	bool playerChangesColor(sf::Color color);
	void computerChangesColor();
	//Selects the best option
	sf::Color computerColor();
	
	//Returns the percentage of area in the board
	double getPlayerPercentage() const;
	double getComputerPercentage() const;

private:
	//Organized board
	void setBoard();
	void setEvenRow(const sf::Vector2f object_size, const float object_width, const int j);
	void setOddRow(const sf::Vector2f object_size, const float object_width, const int j);

	//Updating neighbors to all objects
	void setNeighbors();
	//Updating basic data at the beginning of the game
	void initialBase();

private:
	//members
	std::vector<std::vector<std::shared_ptr<Object>>> m_objects;//olde the data
	int m_sum_of_all_obgects = 0;
	sf::Color m_player_color, m_computer_color;
	
	//Holding pointers to objects that each captured
	std::vector<std::shared_ptr<Object>> m_object_player, m_object_computer;
	//Holding the pointers to the neighbors of the objects he conquered each
	std::vector<std::shared_ptr<Object>> m_neighbors_object_player, m_neighbors_object_computer;
};

