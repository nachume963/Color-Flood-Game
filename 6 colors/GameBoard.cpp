#include "GameBoard.h"

GameBoard::GameBoard()
{
	//For the beginning of a game, order a board
	setBoard();
	setNeighbors();
	initialBase();
}
GameBoard::~GameBoard()
{
}

void GameBoard::draw(sf::RenderWindow & window) const
{
	//draw all objects
	for (size_t j = m_objects.size(); j > 0; j--)
		for (size_t i = m_objects[j - 1].size(); i > 0; i--)
			m_objects[j - 1][i - 1]->draw(window);
}

void GameBoard::resetGame()
{
	//For the beginning of a game, order a board
	setBoard();
	setNeighbors();
	initialBase();
}

bool GameBoard::playerChangesColor(sf::Color color)
{
	//Invalid color check
	if (color == m_computer_color || color == m_player_color)
		return false;
	
	//Update color to all objects captured by the player
	for (size_t i = 0; i < m_object_player.size(); i++)
	{
		m_object_player[i]->setShapeColor(color);
		m_player_color = color;
	}
	
	//Beyond all the neighbors of the player
	for (size_t i = 0; i < m_neighbors_object_player.size(); i++)
		if (m_neighbors_object_player[i]->getShapeColor() == color
			&& m_neighbors_object_player[i]->getWhoOwns() == random)
		{
			//Enclosing the neighbors of the same color and until now they were free
			m_neighbors_object_player[i]->setWhoOwns(player);
			m_object_player.push_back(m_neighbors_object_player[i]);

			//After the capture of a new object, its neighbors are added to the list of neighbors
			for (size_t t = 0; t < m_neighbors_object_player[i]->getNeighbors().size(); t++)
				if(m_neighbors_object_player[i]->getNeighbors()[t]->getWhoOwns() == random)
					m_neighbors_object_player.push_back(m_neighbors_object_player[i]->getNeighbors()[t]);

			//After a new object is captured, remove it from the list of neighbors
			m_neighbors_object_player.erase(m_neighbors_object_player.begin() + i);
		}
	//The move was successful
	return true;
}
void GameBoard::computerChangesColor()
{
	//Accepts a valid color from the function
	sf::Color color = computerColor();

	//Update color to all objects captured by the computer
	for (size_t i = 0; i < m_object_computer.size(); i++)
	{
		m_object_computer[i]->setShapeColor(color);
		m_computer_color = color;
	}

	//Beyond all the neighbors of the computer
	for (size_t i = 0; i < m_neighbors_object_computer.size(); i++)
		if (m_neighbors_object_computer[i]->getShapeColor() == color
			&& m_neighbors_object_computer[i]->getWhoOwns() == random)
		{
			//Enclosing the neighbors of the same color and until now they were free
			m_neighbors_object_computer[i]->setWhoOwns(computer);
			m_object_computer.push_back(m_neighbors_object_computer[i]);

			//After the capture of a new object, its neighbors are added to the list of neighbors
			for (size_t t = 0; t < m_neighbors_object_computer[i]->getNeighbors().size(); t++)
				if (m_neighbors_object_computer[i]->getNeighbors()[t]->getWhoOwns() == random)
					m_neighbors_object_computer.push_back(m_neighbors_object_computer[i]->getNeighbors()[t]);

			//After a new object is captured, remove it from the list of neighbors
			m_neighbors_object_computer.erase(m_neighbors_object_computer.begin() + i);
		}
}
sf::Color GameBoard::computerColor()
{
	sf::Color color, colors[6] = { sf::Color::Blue, sf::Color::Cyan, sf::Color::Green, sf::Color::Magenta, sf::Color::Red, sf::Color::Yellow };
	//int Blue = 0, Cyan = 0, Green = 0, Magenta = 0, Red = 0, Yellow = 0;
	int arr[6] = { 0 }, max = -1, index = -1;

	//Examines the dominant color among neighbors
	for (int i = 0; i < m_neighbors_object_computer.size(); i++)
	{
		color = m_neighbors_object_computer[i]->getShapeColor();
		if (color == sf::Color::Blue &&  m_neighbors_object_computer[i]->getWhoOwns() == random)
			arr[0]++; //Blue++;
		if (color == sf::Color::Cyan &&  m_neighbors_object_computer[i]->getWhoOwns() == random)
			arr[1]++; //Cyan++;
		if (color == sf::Color::Green &&  m_neighbors_object_computer[i]->getWhoOwns() == random)
			arr[2]++; //Green++;
		if (color == sf::Color::Magenta &&  m_neighbors_object_computer[i]->getWhoOwns() == random)
			arr[3]++; //Magenta++;
		if (color == sf::Color::Red &&  m_neighbors_object_computer[i]->getWhoOwns() == random)
			arr[4]++; //Red++;
		if (color == sf::Color::Yellow &&  m_neighbors_object_computer[i]->getWhoOwns() == random)
			arr[5]++; //Yellow++;
	}

	//To get a valid color, you need to check at most 3 options
	for (int t = 0; t < 3; t++)
	{
		//Seeking the most common color
		for (int i = 0; i < 6; i++)
		{
			if (max < arr[i])
			{
				max = arr[i];
				index = i;
			}
		}
		//If invalid, look for the next common color.
		if (colors[index] == m_computer_color || colors[index] == m_player_color)
			max = arr[index] = -1;
		//If valid, returns the common color.
		else return colors[index];
	}
}

double GameBoard::getPlayerPercentage() const
{
	//For not dividing by 0
	if(m_sum_of_all_obgects)
		return ((m_object_player.size() * 100.0) / m_sum_of_all_obgects);
	return 0.0;
}
double GameBoard::getComputerPercentage() const
{
	//For not dividing by 0
	if (m_sum_of_all_obgects)
		return ((m_object_computer.size() * 100.0) / m_sum_of_all_obgects);
	return 0.0;
}


void GameBoard::setBoard()
{
	m_objects.clear();
	
	//Size and width of the objects according to the size of the board
	const sf::Vector2f object_size(OBJECT_SIZE, OBJECT_SIZE);
	const float object_width(BOARD_SIZE.x / NUM_OF_OBJECTS);

	//Fill the board with objects
	for (int j = 0; j < 2 * NUM_OF_OBJECTS + 1; j++)
	{
		if (j % 2 == 0)
			setEvenRow(object_size, object_width, j);
		else if(j % 2 != 0)
			setOddRow(object_size, object_width, j);
	}
}
void GameBoard::setEvenRow(const sf::Vector2f object_size, const float object_width, const int j)
{
	std::vector<std::shared_ptr<Object>> temp_object;

	for (int i = 0; i < NUM_OF_OBJECTS; i++)
	{
		sf::Vector2f object_pos((object_width * i) + POSITON_BOARD.x + object_width / 2,
			((object_width / 2) * j) + POSITON_BOARD.y);
		
		temp_object.push_back(std::make_shared<Object>(object_pos, object_size));
		//Updating the amount of objects
		m_sum_of_all_obgects++;

		//In the top and bottom row the objects become triangles
		if (j == 0)
			temp_object[i]->getShape().setPoint(0, sf::Vector2f(object_size.x, 0.0));
		else if (j == 2 * NUM_OF_OBJECTS)
			temp_object[i]->getShape().setPoint(2, sf::Vector2f(object_size.x, 0.0));
	}
	m_objects.push_back(temp_object);
}
void GameBoard::setOddRow(const sf::Vector2f object_size, const float object_width, const int j)
{
	std::vector<std::shared_ptr<Object>> temp_object;
	for (int i = 0; i < NUM_OF_OBJECTS + 1; i++)
	{
		sf::Vector2f object_pos((object_width * i) + POSITON_BOARD.x,
			((object_width / 2) * j) + POSITON_BOARD.y);

		temp_object.push_back(std::make_shared<Object>(object_pos, object_size));
		//Updating the amount of objects
		m_sum_of_all_obgects++;
	}
	//In each odd row, the first and last organ becomes a triangle
	temp_object[0]->getShape().setPointCount(3);
	temp_object[NUM_OF_OBJECTS]->getShape().setPoint(1, object_size);

	m_objects.push_back(temp_object);
}


void GameBoard::setNeighbors()
{
	//Updating to each object the list of its neighbors
	for (int j = 1; j < m_objects.size(); j++)//Switch from referring to the i first to the j first
	{
		if (j % 2 != 0)
			for (int i = 0; i < m_objects[j].size(); i++)
			{
				if (i == 0)
				{
					m_objects[j][i]->addNeighbor(m_objects[j - 1][i]);
					m_objects[j - 1][i]->addNeighbor(m_objects[j][i]);
					continue;
				}
				if (i == m_objects[j].size() - 1)
				{
					m_objects[j][i]->addNeighbor(m_objects[j - 1][i - 1]);
					m_objects[j - 1][i - 1]->addNeighbor(m_objects[j][i]);
					continue;
				}
				m_objects[j][i]->addNeighbor(m_objects[j - 1][i - 1]);
				m_objects[j][i]->addNeighbor(m_objects[j - 1][i]);
				m_objects[j - 1][i - 1]->addNeighbor(m_objects[j][i]);
				m_objects[j - 1][i]->addNeighbor(m_objects[j][i]);
			}
		else
			for (int i = 0; i < m_objects[j].size(); i++)
			{
				m_objects[j][i]->addNeighbor(m_objects[j - 1][i + 1]);
				m_objects[j][i]->addNeighbor(m_objects[j - 1][i]);
				m_objects[j - 1][i + 1]->addNeighbor(m_objects[j][i]);
				m_objects[j - 1][i]->addNeighbor(m_objects[j][i]);
			}
	}
}
void GameBoard::initialBase()
{	
	//Updating basic data for the player
	m_objects[2 * NUM_OF_OBJECTS][0]->setWhoOwns(player);
	m_player_color = m_objects[2 * NUM_OF_OBJECTS][0]->getShapeColor();
	m_object_player.push_back(m_objects[2 * NUM_OF_OBJECTS][0]);
	m_neighbors_object_player = m_objects[2 * NUM_OF_OBJECTS][0]->getNeighbors();
	
	//Updating basic data for your computer
	m_objects[0][NUM_OF_OBJECTS - 1]->setWhoOwns(computer);
	m_computer_color = m_objects[0][NUM_OF_OBJECTS - 1]->getShapeColor();
	m_object_computer.push_back(m_objects[0][NUM_OF_OBJECTS -1]);
	m_neighbors_object_computer = m_objects[0][NUM_OF_OBJECTS -1]->getNeighbors();
}
