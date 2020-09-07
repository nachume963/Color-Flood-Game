#include "ResetGame.h"
#include "Controller.h"


ResetGame::ResetGame()
	:Button(sf::Vector2f(SIZE_BUTTON.x + POSITON_MENU.x, POSITON_MENU.y),
		SIZE_BUTTON, "ResetGame.png")
{
}
ResetGame::~ResetGame()
{
}

void ResetGame::click(Controller & controller)
{
	controller.resetGame();
}
