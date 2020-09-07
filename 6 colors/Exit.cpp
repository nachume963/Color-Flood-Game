#include "Exit.h"
#include "Controller.h"


Exit::Exit()
	:Button(POSITON_MENU, SIZE_BUTTON, "Exit.png")
{
}
Exit::~Exit()
{
}

void Exit::click(Controller & controller)
{
	controller.finishGame();
}
