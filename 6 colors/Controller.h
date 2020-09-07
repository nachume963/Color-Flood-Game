#pragma once
#include "Constants.h"

#include "Menu.h"
#include "GameBoard.h"

class Controller
{
public:
	Controller();
	~Controller();
	
	//the main fanction that run the game
	void run();

	//Functions that are triggered by the user's request
	void finishGame();
	void resetGame();
	void ChangesColor(sf::Color color);

private:
	//Functions that use the controller
	void draw(sf::RenderWindow & window) const;
	void PrintSnapshot(sf::RenderWindow & window) const;
	void HandleEvents();
	bool CheckVictory(std::string & to_print) const;

private:
	//members
	sf::RenderWindow m_window;
	GameBoard m_board;
	Menu m_menu;

	std::string m_turn = "player's turn"; //Whose turn is now
	std::string m_print_by_victory = " "; //Whose won
	bool m_stop = false;				//Stops the game when someone wins
};

