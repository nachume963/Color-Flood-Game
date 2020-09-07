#include "Controller.h"


Controller::Controller()
	:m_window(sf::VideoMode(int(WINDOE_SIZE.x), int(WINDOE_SIZE.y)),
		"6 colors. prod by. Haim Fisher & Nachum Ehrlich", sf::Style::Default)
{
}
Controller::~Controller()
{
}

void Controller::run()
{
	//The game runs as long as the window is open
	while (m_window.isOpen())
	{
		//Waiting for user action
		HandleEvents();
		//Checks if someone won the game
		m_stop = CheckVictory(m_print_by_victory);
		//drow
		draw(m_window);
	}
}

void Controller::finishGame()
{
	//Closes the window - finishes the game
	m_window.close();
}
void Controller::resetGame()
{
	//A new game begins
	m_board.resetGame();
}
void Controller::ChangesColor(sf::Color color)
{
	//Replaces player color if it's valid
	if (m_board.playerChangesColor(color))
	{
		//Updating that it's now time for the computer's turn to play
		m_turn = "computer's turn";
		//drow
		draw(m_window);
		//Calling the computer to make its move
		m_board.computerChangesColor();
	}
	//Updating that it's now time for the player's turn to play, again
	m_turn = "player's turn";
}


void Controller::draw(sf::RenderWindow & window) const
{
	//draw teh board himself
	window.clear(sf::Color(203, 187, 160));

	m_menu.draw(window);
	m_board.draw(window);

	PrintSnapshot(window);

	window.display();	
}
void Controller::PrintSnapshot(sf::RenderWindow & window) const
{
	sf::Font aaa;
	aaa.loadFromFile("aaa.ttf");

	sf::Text whose_turn(m_turn, aaa, 30);
	whose_turn.setPosition(sf::Vector2f(25, 840));
	whose_turn.setFillColor(sf::Color::Black);
	window.draw(whose_turn);

	//Calculates the percentages of each on the board
	std::string status_line = "The player: " + std::to_string(m_board.getPlayerPercentage()) +
		"			the computer: " + std::to_string(m_board.getComputerPercentage());

	sf::Text status(status_line, aaa, 45);
	status.setPosition(sf::Vector2f(20, 925));
	status.setFillColor(sf::Color::Black);
	window.draw(status);

	//Only if someone won
	if (m_stop) 
	{
		sf::Text victory(m_print_by_victory, aaa, 70);
		victory.setPosition(sf::Vector2f(350, 200));
		victory.setFillColor(sf::Color::Black);
		victory.rotate(30);
		window.draw(victory);
	}
}

void Controller::HandleEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			finishGame();
			break;
		case sf::Event::KeyPressed:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				finishGame();
			if (m_stop && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				//To return to another game
				m_stop = false;
				resetGame();
			}
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left && !m_stop)
			{
				//Mapping the click
				sf::Vector2f mouseButtonPos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
				//Calls to button function
				m_menu.click(*this, mouseButtonPos);
				break;
			}
		}
	}
}

bool Controller::CheckVictory(std::string & to_print)const
{
	//If the player or computer passes the 50% of the board is the winner
	if (m_board.getPlayerPercentage() >= 50.0)
	{
			to_print = " yuo win!!! \n Enter to start a new game";
			return true;
	}	
	if (m_board.getComputerPercentage() >= 50.0)
	{
		to_print = " yuo lose!!! \n Enter to start a new game";
		return true;
	}
	return false;
}
